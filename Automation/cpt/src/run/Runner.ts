import fs from "fs";
import { ChildProcess } from "child_process";
import quote from "../utils/quote";
import RunnerInitError from "./types/RunnerInitError";
import inferLanguage from "./helpers/inferLanguage";
import getLanguageEntry from "./helpers/getLanguageEntry";
import compileUsingArgs from "./helpers/compileUsingArgs";
import spawnerUsingArgs from "./helpers/spawnerUsingArgs";

class Run extends Promise<{
	code: number | null;
	signal: NodeJS.Signals | null;
}> {
	constructor(readonly child: ChildProcess) {
		super((resolve, reject) => {
			child.on("exit", (code, signal) => {
				resolve({ code, signal });
			});

			child.on("error", (err) => {
				this.kill();
				reject(err);
			});
		});

		this.child = child;
	}

	kill() {
		// PIDs can be reassigned once a process ends. To avoid the possibility of
		// killing an unrelated process, check first if the process is still alive.
		if (this.child.exitCode === null && this.child.signalCode === null)
			this.child.kill();
	}
}
export default class Runner {
	readonly language: string;
	readonly spawn: ReturnType<typeof spawnerUsingArgs>;

	constructor(
		readonly filePath: string,
		language?: string
	) {
		try {
			fs.accessSync(filePath, fs.constants.R_OK);
		} catch (err: unknown) {
			throw new RunnerInitError(this, RunnerInitError.Code.ACCESS_ERROR, {
				cause: err,
			});
		}

		language ??= inferLanguage(filePath);
		if (!language)
			throw new RunnerInitError(
				this,
				RunnerInitError.Code.LANGUAGE_INFERENCE_ERROR
			);
		this.language = language;

		const languageEntry = getLanguageEntry(language);
		if (!languageEntry)
			throw new RunnerInitError(
				this,
				RunnerInitError.Code.LANGUAGE_SUPPORT_ERROR
			);

		let compileArgs, spawnArgs;
		try {
			({ compileArgs, spawnArgs } = languageEntry(filePath));
		} catch (err) {
			throw new RunnerInitError(
				this,
				RunnerInitError.Code.LANGUAGE_ENTRY_ERROR,
				{ cause: err }
			);
		}

		if (compileArgs)
			try {
				compileUsingArgs(compileArgs);
			} catch (err) {
				throw new RunnerInitError(
					this,
					RunnerInitError.Code.COMPILATION_ERROR,
					{ cause: err }
				);
			}

		this.spawn = spawnerUsingArgs(spawnArgs);
	}

	run(
		options?: Parameters<typeof this.spawn>[0]
	): Promise<{ code: number | null; signal: NodeJS.Signals | null }> {
		return new Run(this.spawn(options));
	}

	toString(): string {
		return `${quote(this.filePath)} (${this.language})`;
	}
}
