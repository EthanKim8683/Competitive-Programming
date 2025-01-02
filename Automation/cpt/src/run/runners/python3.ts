import fs from "fs";

import { RunBase, RunnerInterface, RunnerOptions, RunOptions } from "../base";

export default class Python3Runner implements RunnerInterface {
	readonly promise;
	private _settled = false;
	private _runnable = false;

	constructor(
		readonly filePath: string,
		_options: RunnerOptions = {}
	) {
		const { promise, resolve, reject } = Promise.withResolvers<Python3Runner>();
		this.promise = promise;

		// Is the non-existence of the program a compile-time or runtime error if
		// the program is interpreted?
		fs.access(filePath, fs.constants.R_OK, (err) => {
			this._settled = true;
			if (err) reject(err);
			else {
				this._runnable = true;
				resolve(this);
			}
		});
	}

	private _run(options?: RunOptions) {
		return new RunBase("/opt/homebrew/bin/python3", [this.filePath], options);
	}

	kill() {}

	get settled() {
		return this._settled;
	}

	get run() {
		if (this._runnable) return this._run;
	}
}
