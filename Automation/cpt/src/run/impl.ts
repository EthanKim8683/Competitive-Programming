import { spawn } from "child_process";
import fs, { ReadStream } from "fs";

import { ProcessInterface, RunOptions } from "./base";

export class SpawnProcess implements ProcessInterface {
	readonly promise;
	readonly child;
	private _abortController = new AbortController();

	constructor(
		command: string,
		args: string[] = [],
		{ spawnOptions = {} }: RunOptions = {}
	) {
		const { promise, resolve, reject } = Promise.withResolvers<SpawnProcess>();
		this.promise = promise;

		this.child = spawn(command, args, {
			...spawnOptions,
			signal: this._abortController.signal,
		});

		this.child.on("exit", () => resolve(this));

		this.child.on("error", (err) => {
			// AbortErrors aren't real errors. We already know the process has been
			// aborted because we aborted it.
			if (err.name === "AbortError") return;
			reject(err);
		});
	}

	kill() {
		this._abortController.abort();
	}
}

export class ReadStreamProcess implements ProcessInterface {
	readonly promise: Promise<ProcessInterface>;
	readonly stream: ReadStream;
	private _abortController = new AbortController();

	constructor(filePath: string, _options?: RunOptions) {
		const { promise, resolve, reject } =
			Promise.withResolvers<ReadStreamProcess>();
		this.promise = promise;

		this.stream = fs.createReadStream(filePath, {
			signal: this._abortController.signal,
		});

		this.stream.on("close", () => resolve(this));

		this.stream.on("error", (err) => {
			if (err.name === "AbortError") return;
			reject(err);
		});
	}

	kill(): void {
		this._abortController.abort();
	}
}
