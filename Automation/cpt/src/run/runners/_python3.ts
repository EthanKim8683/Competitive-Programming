import fs from "fs";

import {
	EntryInterface,
	IniterInterface,
	IniterOptions,
	Run,
	RunnerInterface,
	RunOptions,
} from "../base";

class Python3Runner implements RunnerInterface {
	constructor(readonly initer: Python3Initer) {}

	run(options?: RunOptions): Run {
		return new Run(
			"/opt/homebrew/bin/python3",
			[this.initer.filePath],
			options
		);
	}
}

class Python3Initer implements IniterInterface {
	readonly promise: Promise<Python3Runner>;

	// TODO: Handle options.
	constructor(
		readonly filePath: string,
		_options?: IniterOptions
	) {
		const { promise, resolve, reject } = Promise.withResolvers<Python3Runner>();
		this.promise = promise;

		// Is the non-existence of the program a compile-time or runtime error if
		// the program is interpreted?
		fs.access(filePath, fs.constants.R_OK, (err) => {
			if (err) reject(err);
			else resolve(new Python3Runner(this));
		});
	}

	kill(): void {}
}

export function isPython3Runner(
	runner: RunnerInterface
): runner is Python3Runner {
	return runner instanceof Python3Runner;
}

export function isPython3Initer(
	initer: IniterInterface
): initer is Python3Initer {
	return initer instanceof Python3Initer;
}

const python3Entry: EntryInterface = (
	filePath: string,
	options?: IniterOptions
): Python3Initer => new Python3Initer(filePath, options);
export default python3Entry;
