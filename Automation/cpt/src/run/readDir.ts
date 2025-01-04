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

class ReadDirIniter extends Initer implements Initer {
	constructor(readonly dirPath: string) {
		const { promise, resolve, reject } =
			Promise.withResolvers<ReadDirInvoker>();
		super(promise);

		fs.readdir(dirPath, { withFileTypes: true }, (err, dirents) => {
			if (err)
				return reject(
					new InitError(this, "Could not read directory", { cause: err })
				);

			resolve(
				new ReadDirInvoker(
					this,
					dirents
						.filter((dirent) => dirent.isFile())
						.map((dirent) => dirent.name)
				)
			);
		});
	}
}

class ReadDirInvoker implements Invoker {
	constructor(
		readonly initer: ReadDirIniter,
		readonly fileBasenames: string[]
	) {}

	invoke(fileBasename: string): ReadFileProcess {
		if (!this.fileBasenames.includes(fileBasename))
			throw new InvokeError(this, "Could not find file in directory", {
				cause: { fileBasename, knownFileBasenames: this.fileBasenames },
			});

		return new ReadFileProcess(
			this,
			path.join(this.initer.dirPath, fileBasename)
		);
	}
}

class ReadFileProcess extends Process implements Process {
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
		super(promise, () => this._abortController.abort());

		this.stream = fs.createReadStream(filePath, {
			signal: this._abortController.signal,
		});

		this.stdin = new NullWritable();
		this.stdout = this.stream;
		this.stderr = new NullReadable();

		this.stream.on("close", () => resolve());

		this.stream.on("error", (err: NodeJS.ErrnoException) => {
			if (err.name === "AbortError")
				return reject(
					new ProcessError(this, "Process aborted", { cause: err })
				);

			return reject(
				new ProcessError(this, "Could not open file", { cause: err })
			);
		});
	}
}

const readDir = (dirPath: string): ReadDirIniter => new ReadDirIniter(dirPath);
export default readDir;
