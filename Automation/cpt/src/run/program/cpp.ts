import path from "path";
import os from "os";
import { ChildProcess } from "child_process";
import crypto from "crypto";

import { exec } from "../../lib/child_process";
import {
	InitError,
	Process,
	ProgramIniter,
	ProgramInitOptions,
	ProgramInvokeOptions,
	ProgramInvoker,
	ProgramModule,
	ProgramProcess,
} from "../base";

class CppIniter implements ProgramIniter {
	readonly promise: Promise<CppInvoker>;
	readonly child: ChildProcess;
	readonly compilerArgs: string[];
	private _compilerStderr: string | undefined = undefined;
	private _abortController = new AbortController();

	constructor(
		readonly programPath: string,
		{ cppOptions: { std = "c++20" } = {} }: ProgramInitOptions = {}
	) {
		const { promise, resolve, reject } = Promise.withResolvers<CppInvoker>();
		this.promise = promise;

		const fileName = path.parse(programPath).name,
			randomHex = crypto.randomBytes(6).toString("hex"),
			executablePath = path.relative(
				process.cwd(),
				path.join(os.tmpdir(), `${fileName}-${randomHex}`)
			);

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
			{ signal: this._abortController.signal },
			// _error represents all errors, even those thrown by the process itself,
			// which don't indicate anything on CPT's end.
			(_error, _stdout, stderr) => {
				this._compilerStderr = stderr.toString("utf-8") || undefined;

				const { exitCode, signalCode } = this.child;
				if (exitCode)
					return reject(
						new InitError(this, "Compiler exited with non-zero exit code")
					);
				else if (signalCode)
					return reject(new InitError(this, "Compilation terminated"));

				resolve(new CppInvoker(this, executablePath));
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

	get compilerStderr(): string | undefined {
		return this._compilerStderr;
	}
}

class CppInvoker implements ProgramInvoker {
	constructor(
		readonly initer: CppIniter,
		readonly executablePath: string
	) {}

	invoke(options?: ProgramInvokeOptions): Process {
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
