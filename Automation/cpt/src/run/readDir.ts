import fs from "fs";
import path from "path";

import {
	ExitStatus,
	Initer,
	InitError,
	InvokeError,
	Invoker,
	Process,
} from "./base";
import { NullReadable, NullWritable } from "../lib/stream";

class ReadDirIniter
	extends Initer<ReadDirInvoker>
	implements Initer<ReadDirInvoker>
{
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
	warning: string | undefined = undefined;

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
		const { promise, resolve, reject } = Promise.withResolvers<ExitStatus>();
		super(promise, () => this._abortController.abort());

		this.stream = fs.createReadStream(filePath, {
			signal: this._abortController.signal,
		});

		this.stdin = new NullWritable();
		this.stdout = this.stream;
		this.stderr = new NullReadable();

		this.stream.on("close", () => resolve({ exitCode: 0, signalCode: null }));

		this.stream.on("error", (err) => {
			if (err.name === "AbortError")
				return resolve({ exitCode: null, signalCode: "SIGABRT" });

			// I don't know enough about the kinds of errors ReadStreams can throw
			// to handle them thoroughly.
			// TODO: Research ReadStream errors and handle appropriately.
			reject(err);
		});
	}
}

const readDir = (dirPath: string): ReadDirIniter => new ReadDirIniter(dirPath);
export default readDir;
