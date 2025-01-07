import fs from "fs";

import { InitError } from "../base";
import {
	ProgramIniter,
	ProgramInvoker,
	ProgramModule,
	ProgramProcess,
} from "./base";
import { SpawnOptions } from "child_process";

class Python3Initer
	extends ProgramIniter<Python3Invoker>
	implements ProgramIniter<Python3Invoker>
{
	constructor(readonly programPath: string) {
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
	readonly warning: string | undefined = undefined;

	constructor(readonly initer: Python3Initer) {}

	invoke(options?: SpawnOptions): ProgramProcess {
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

interface Python3Module extends ProgramModule {
	(programPath: string): Python3Initer;
}

const python3: Python3Module = (programPath: string): Python3Initer =>
	new Python3Initer(programPath);
export default python3;
