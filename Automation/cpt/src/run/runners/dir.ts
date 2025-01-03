import fs from "fs";
import path from "path";

import {
	EntryInterface,
	IniterInterface,
	InitOptions,
	RunnerInterface,
	RunOptions,
} from "../base";
import { ReadStreamProcess } from "../impl";

class DirIniter implements IniterInterface {
	readonly promise: Promise<DirRunner>;

	constructor(
		readonly filePath: string,
		_options?: InitOptions
	) {
		const { promise, resolve, reject } = Promise.withResolvers<DirRunner>();
		this.promise = promise;

		fs.readdir(filePath, (err, files) => {
			if (err) reject(err);
			else resolve(new DirRunner(this, files));
		});
	}

	// TODO: Find a way to kill readdir.
	kill(): void {}
}

class DirRunner implements RunnerInterface {
	constructor(
		readonly initer: IniterInterface,
		readonly basenames: string[]
	) {}

	run({ dirBasename: basename }: RunOptions = {}): ReadStreamProcess {
		const filePath =
			basename !== undefined
				? path.join(this.initer.filePath, basename)
				: "/dev/null";

		return new ReadStreamProcess(filePath);
	}
}

export function isDirRunner(runner: RunnerInterface): runner is DirRunner {
	return runner instanceof DirRunner;
}

export function isDirIniter(initer: IniterInterface): initer is DirIniter {
	return initer instanceof DirIniter;
}

const dirEntry: EntryInterface = (
	filePath: string,
	options?: InitOptions
): DirIniter => new DirIniter(filePath, options);
export default dirEntry;
