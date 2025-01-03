import fs from "fs";

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

class Python3Initer implements ProgramIniter {
	readonly promise;

	constructor(
		readonly programPath: string,
		_options?: ProgramInitOptions
	) {
		const { promise, resolve, reject } =
			Promise.withResolvers<Python3Invoker>();
		this.promise = promise;

		fs.access(programPath, fs.constants.R_OK, (err) => {
			if (err) {
				if (
					err.syscall === "access" &&
					(err.code === "ENOENT" || err.code === "EACCES")
				)
					return reject(
						new InitError(this, "Could not access program", { cause: err })
					);

				return reject(err);
			}

			resolve(new Python3Invoker(this));
		});
	}

	kill(): void {}
}

class Python3Invoker implements ProgramInvoker {
	constructor(readonly initer: Python3Initer) {}

	invoke(options?: ProgramInvokeOptions): Process {
		return new ProgramProcess(
			this,
			"/opt/homebrew/bin/python3",
			[this.initer.programPath],
			options
		);
	}
}

export function isPython3Initer(value: any): value is Python3Initer {
	return value instanceof Python3Initer;
}

export function isPython3Invoker(value: any): value is Python3Invoker {
	return value instanceof Python3Invoker;
}

const python3: ProgramModule = (
	programPath: string,
	options?: ProgramInitOptions
): ProgramIniter => new Python3Initer(programPath, options);
export default python3;
