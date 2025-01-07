import path from "path";
import { ChildProcess, SpawnOptions } from "child_process";

import { exec } from "../../lib/child_process";
import { InitError } from "../base";
import {
	ProgramIniter,
	ProgramInvoker,
	ProgramModule,
	ProgramProcess,
} from "./base";
import { absolute } from "../../lib/path";

type CppOptions = {
	std?: "c++98" | "c++03" | "c++11" | "c++14" | "c++17" | "c++20" | "c++23";
};

class CppIniter
	extends ProgramIniter<CppInvoker>
	implements ProgramIniter<CppInvoker>
{
	readonly child: ChildProcess;
	readonly args: string[];
	private _abortController = new AbortController();

	constructor(
		readonly programPath: string,
		{ std = "c++20" }: CppOptions = {}
	) {
		const { promise, resolve, reject } = Promise.withResolvers<CppInvoker>();
		super(promise, () => this._abortController.abort());

		const { dir, name } = path.parse(
			path.relative(process.cwd(), absolute(programPath))
		);
		// Prefixing the executablePath with "./" ensures it will always be seen as
		// a relative path.
		const executablePath = "./" + path.join(dir, name);

		this.args = [
			"/opt/homebrew/bin/g++-14",
			"-o",
			executablePath,
			programPath,
			"-O2",
			`-std=${std}`,
			"-DETHANKIM8683",
		];

		this.child = exec(
			this.args[0],
			this.args.slice(1),
			{ signal: this._abortController.signal },
			(error, _stdout, stderr) => {
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

				const warning = stderr.toString("utf8") || undefined;
				resolve(new CppInvoker(this, executablePath, warning));
			}
		);
	}
}

class CppInvoker implements ProgramInvoker {
	constructor(
		readonly initer: CppIniter,
		readonly executablePath: string,
		readonly warning: string | undefined
	) {}

	invoke(options?: SpawnOptions): ProgramProcess {
		return new ProgramProcess(this, this.executablePath, [], options);
	}
}

export function isCppIniter(value: any): value is CppIniter {
	return value instanceof CppIniter;
}

export function isCppInvoker(value: any): value is CppInvoker {
	return value instanceof CppInvoker;
}

interface CppModule extends ProgramModule {
	(programPath: string, cppOptions?: CppOptions): CppIniter;
}

const cpp: CppModule = (
	programPath: string,
	cppOptions?: CppOptions
): CppIniter => new CppIniter(programPath, cppOptions);
export default cpp;
