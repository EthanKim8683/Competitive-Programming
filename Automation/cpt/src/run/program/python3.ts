import fs from "fs";

import { InitError } from "../base";
import {
	ProgramIniter,
	ProgramInitOptions,
	ProgramInvokeOptions,
	ProgramInvoker,
	ProgramModule,
	ProgramProcess,
} from "./base";

class Python3Initer extends ProgramIniter implements ProgramIniter {
	constructor(
		readonly programPath: string,
		_options?: ProgramInitOptions
	) {
		const { promise, resolve, reject } =
			Promise.withResolvers<Python3Invoker>();
		super(promise);

		// No compilation needed, so just make sure everything's ready to go while
		// we have time.
		fs.access(programPath, fs.constants.R_OK, (err) => {
			if (err)
				return reject(
					new InitError(this, "Could not access program", { cause: err })
				);

			resolve(new Python3Invoker(this));
		});
	}
}

class Python3Invoker implements ProgramInvoker {
	constructor(readonly initer: Python3Initer) {}

	invoke(options?: ProgramInvokeOptions): ProgramProcess {
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
