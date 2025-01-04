import path from "path";
import { ChildProcess } from "child_process";

import { exec } from "../../lib/child_process";
import { InitError } from "../base";
import {
	ProgramIniter,
	ProgramInitOptions,
	ProgramInvokeOptions,
	ProgramInvoker,
	ProgramModule,
	ProgramProcess,
} from "./base";
import { absolute } from "../../lib/path";

class CppIniter extends ProgramIniter implements ProgramIniter {
	readonly child: ChildProcess;
	readonly compilerArgs: string[];
	private _compilerStderr: string | undefined = undefined;
	private _abortController = new AbortController();

	constructor(
		readonly programPath: string,
		{ execOptions, cppOptions: { std = "c++20" } = {} }: ProgramInitOptions = {}
	) {
		const { promise, resolve, reject } = Promise.withResolvers<CppInvoker>();
		super(promise, () => this._abortController.abort());

		const { dir, name } = path.parse(
			path.relative(process.cwd(), absolute(programPath))
		);
		// Prefixing the executablePath with "./" ensures it will always be seen as
		// a relative path.
		const executablePath = "./" + path.join(dir, name);

		this.compilerArgs = [
			"/opt/homebrew/bin/g++-14",
			"-o",
			executablePath,
			programPath,
			"-O2",
			`-std=${std}`,
			"-DETHANKIM8683",
		];

		this.child = exec(
			this.compilerArgs[0],
			this.compilerArgs.slice(1),
			{ ...execOptions, signal: this._abortController.signal },
			(error, _stdout, stderr) => {
				this._compilerStderr = stderr.toString("utf8") || undefined;

				if (error) {
					if (error.name === "AbortError")
						return reject(
							new InitError(this, "Compilation aborted", { cause: error })
						);

					// If the process doesn't exit gracefully, exec treats it as an error.
					const { exitCode, signalCode } = this.child;
					if (exitCode)
						return reject(
							new InitError(this, "Compiler exited with non-zero exit code", {
								cause: error,
							})
						);
					if (signalCode)
						return reject(
							new InitError(this, "Compilation terminated", {
								cause: error,
							})
						);

					return reject(error);
				}

				resolve(new CppInvoker(this, executablePath));
			}
		);
	}

	get compilerStderr(): string | undefined {
		return this._compilerStderr;
	}
}

class CppInvoker implements ProgramInvoker {
	constructor(
		readonly initer: CppIniter,
		readonly executablePath: string
	) {}

	invoke(options?: ProgramInvokeOptions): ProgramProcess {
		return new ProgramProcess(this, this.executablePath, [], options);
	}
}

export function isCppIniter(value: any): value is CppIniter {
	return value instanceof CppIniter;
}

export function isCppInvoker(value: any): value is CppInvoker {
	return value instanceof CppInvoker;
}

const cpp: ProgramModule = (
	programPath: string,
	options?: ProgramInitOptions
): ProgramIniter => new CppIniter(programPath, options);
export default cpp;
