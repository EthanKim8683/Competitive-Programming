import fs from "fs";
import path from "path";

import {
	Initer,
	InitError,
	InvokeError,
	Invoker,
	Process,
	ProcessError,
} from "./base";
import { NullReadable, NullWritable } from "../lib/stream";

class ReadDirIniter implements Initer {
	readonly promise;

	constructor(readonly dirPath: string) {
		const { promise, resolve, reject } =
			Promise.withResolvers<ReadDirInvoker>();
		this.promise = promise;

		fs.readdir(dirPath, (err, files) => {
			if (err) {
				if (
					err.syscall === "scandir" &&
					(err.code === "ENOENT" || err.code === "EACCES")
				)
					reject(
						new InitError(this, "Could not read directory", { cause: err })
					);

				return reject(err);
			}

			resolve(new ReadDirInvoker(this, files));
		});
	}

	kill(): void {}
}

class ReadDirInvoker implements Invoker {
	constructor(
		readonly initer: ReadDirIniter,
		readonly fileBasenames: string[]
	) {}

	invoke(fileBasename: string): ReadFileProcess {
		if (!this.fileBasenames.includes(fileBasename))
			throw new InvokeError(this, "Could not find file in directory", {
				cause: { fileBasename, fileBasenames: this.fileBasenames },
			});

		return new ReadFileProcess(
			this,
			path.join(this.initer.dirPath, fileBasename)
		);
	}
}

class ReadFileProcess implements Process {
	readonly promise;
	readonly stream;
	readonly stdin;
	readonly stdout;
	readonly stderr;
	private _abortController = new AbortController();

	constructor(
		readonly invoker: Invoker,
		filePath: string
	) {
		const { promise, resolve, reject } = Promise.withResolvers<void>();
		this.promise = promise;

		this.stream = fs.createReadStream(filePath, {
			signal: this._abortController.signal,
		});

		this.stdin = new NullWritable();
		this.stdout = this.stream;
		this.stderr = new NullReadable();

		this.stream.on("close", () => resolve());

		this.stream.on("error", (err: NodeJS.ErrnoException) => {
			if (err.name === "AbortError") return;

			if (
				err.syscall === "open" &&
				(err.code === "ENOENT" || err.code === "EACCESS")
			)
				return reject(
					new ProcessError(this, "Could not open file", { cause: err })
				);

			reject(err);
		});
	}

	kill(): void {
		this._abortController.abort();
	}
}

const readDir = (dirPath: string): ReadDirIniter => new ReadDirIniter(dirPath);
export default readDir;
