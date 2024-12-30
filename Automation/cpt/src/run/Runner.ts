import fs from "fs";
import quote from "../utils/quote";
import RunnerInitError from "./types/RunnerInitError";
import RunnerRuntimeError from "./types/RunnerRuntimeError";
import RunnerRunPromise from "./types/RunnerRunPromise";
import inferLanguage from "./helpers/inferLanguage";
import getLanguageEntry from "./helpers/getLanguageEntry";
import compileUsingArgs from "./helpers/compileUsingArgs";
import spawnerUsingArgs from "./helpers/spawnerUsingArgs";

export default class Runner {
	public static InitError = RunnerInitError;
	public static RuntimeError = RunnerRuntimeError;
	public static RunPromise = RunnerRunPromise;

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

	run(options?: Parameters<typeof this.spawn>[0]): RunnerRunPromise {
		return new RunnerRunPromise(this, options);
	}

	toString(): string {
		return `${quote(this.filePath)} (${this.language})`;
	}
}
