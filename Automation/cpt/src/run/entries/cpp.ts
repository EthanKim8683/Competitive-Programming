import path from "path";
import os from "os";

import {
	EntryInterface,
	IniterInterface,
	InitOptions,
	InitError,
	RunnerInterface,
	RunOptions,
} from "../base";
import { exec } from "../../lib/child_process";
import { ChildProcess } from "child_process";
import { SpawnProcess } from "../impl";

class CppIniter implements IniterInterface {
	readonly promise: Promise<CppRunner>;
	readonly compilerArgs: string[];
	readonly child: ChildProcess;
	private _abortController = new AbortController();

	constructor(
		readonly filePath: string,
		{ cppOptions: { std = "c++20" } = {}, execOptions = {} }: InitOptions = {}
	) {
		const { promise, resolve, reject } = Promise.withResolvers<CppRunner>();
		this.promise = promise;

		// As long as two instances of CPT aren't running at the same time, the
		// odds of clashing are slim. Maybe in the future, I'll add a couple random
		// characters at the end.
		const fileName = path.parse(filePath).name;
		const executablePath = path.relative(
			process.cwd(),
			path.join(os.tmpdir(), fileName)
		);

		this.compilerArgs = [
			"/opt/homebrew/bin/g++-14",
			"-o",
			executablePath,
			filePath,
			"-O2",
			`-std=${std}`,
			"-DETHANKIM8683",
		];
		this.child = exec(
			this.compilerArgs[0],
			this.compilerArgs.slice(1),
			{ ...execOptions, signal: this._abortController.signal },
			// _error represents all errors, even those thrown by the process itself,
			// which don't indicate anything on CPT's end.
			(_error, _stdout, stderr) => {
				const { exitCode, signalCode } = this.child;
				if (exitCode || signalCode)
					reject(
						new InitError(
							this,
							exitCode
								? `Compiler exited with non-zero exit code: ${exitCode}`
								: `Compilation terminated with signal: '${signalCode}'`
						)
					);

				const compilerStderr = stderr.toString("utf-8") || undefined;
				resolve(new CppRunner(this, executablePath, compilerStderr));
			}
		);

		this.child.on("error", (err) => {
			if (err.name === "AbortError") return;
			reject(err);
		});
	}

	kill(): void {
		this._abortController.abort();
	}
}

class CppRunner implements RunnerInterface {
	constructor(
		readonly initer: CppIniter,
		readonly executablePath: string,
		readonly compilerStderr: string | undefined
	) {}

	run(options?: RunOptions): SpawnProcess {
		return new SpawnProcess(this.executablePath, [], options);
	}
}

export function isCppRunner(runner: RunnerInterface): runner is CppRunner {
	return runner instanceof CppRunner;
}

export function isCppIniter(initer: IniterInterface): initer is CppIniter {
	return initer instanceof CppIniter;
}

const cppEntry: EntryInterface = (
	filePath: string,
	options?: InitOptions
): CppIniter => new CppIniter(filePath, options);
export default cppEntry;
