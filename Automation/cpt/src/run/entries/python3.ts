import fs from "fs";

import {
	EntryInterface,
	IniterInterface,
	InitError,
	InitOptions,
	RunnerInterface,
	RunOptions,
} from "../base";
import { SpawnProcess } from "../impl";

class Python3Initer implements IniterInterface {
	readonly promise: Promise<Python3Runner>;

	// TODO: Handle options.
	constructor(
		readonly filePath: string,
		_options?: InitOptions
	) {
		const { promise, resolve, reject } = Promise.withResolvers<Python3Runner>();
		this.promise = promise;

		// Is the non-existence of the program a compile-time or runtime error if
		// the program is interpreted?
		fs.access(filePath, fs.constants.R_OK, (err) => {
			if (err)
				reject(new InitError(this, "Could not access program", { cause: err }));
			else resolve(new Python3Runner(this));
		});
	}

	kill(): void {}
}
class Python3Runner implements RunnerInterface {
	constructor(readonly initer: Python3Initer) {}

	run(options?: RunOptions): SpawnProcess {
		return new SpawnProcess(
			"/opt/homebrew/bin/python3",
			[this.initer.filePath],
			options
		);
	}
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
	options?: InitOptions
): Python3Initer => new Python3Initer(filePath, options);
export default python3Entry;
