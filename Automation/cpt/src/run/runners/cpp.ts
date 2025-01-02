import os from "os";
import path from "path";

import { RunBase, RunnerInterface, RunnerOptions, RunOptions } from "../base";
import { exec } from "../../lib/child_process";

export default class CppRunner implements RunnerInterface {
	readonly promise;
	readonly child;
	readonly compilerArgs: string[];
	private _settled = false;
	private _runnable = false;
	private _abortController = new AbortController();
	private _executablePath?: string = undefined;
	private _compilerStderr?: string = undefined;

	constructor(
		readonly filePath: string,
		{ cppStd = "c++20", ...options }: RunnerOptions = {}
	) {
		const { promise, resolve, reject } = Promise.withResolvers<CppRunner>();
		this.promise = promise;

		// As long as two instances of CPT aren't running at the same time, the
		// odds of clashing are slim. Maybe in the future, I'll add a couple random
		// characters at the end.
		const fileName = path.parse(filePath).name;
		const executablePath = path.join(os.tmpdir(), fileName);

		this.compilerArgs = [
			"/opt/homebrew/bin/g++-14",
			"-o",
			executablePath,
			filePath,
			"-O2",
			`-std=${cppStd}`,
			"-DETHANKIM8683",
		];
		this.child = exec(
			this.compilerArgs[0],
			this.compilerArgs.slice(1),
			{ ...options, signal: this._abortController.signal },
			// _error represents all errors, even those thrown by the process itself
			// and don't indicate anything on CPT's end.
			(_error, _stdout, stderr) => {
				if (!(this.child.exitCode || this.child.signalCode)) {
					this._executablePath = executablePath;
					this._runnable = true;
				}

				this._compilerStderr = stderr.toString("utf-8") || undefined;
				this._settled = true;
				resolve(this);
			}
		);

		this.child.on("error", (err) => {
			if (err.name === "AbortError") return;
			reject(err);
		});
	}

	private _run(options?: RunOptions) {
		return new RunBase(
			path.relative(process.cwd(), this._executablePath!),
			[],
			options
		);
	}

	kill() {
		this._abortController.abort();
	}

	get settled() {
		return this._settled;
	}

	get run() {
		if (this._runnable) return this._run;
	}

	get executablePath() {
		return this._executablePath;
	}

	get compilerStderr() {
		return this._compilerStderr;
	}
}
