import path from "path";
import fs from "fs";

import { RunnerInterface, RunnerOptions } from "./base";
import { quote, tj } from "../util";

export function getLanguage(filePath: string): string | undefined {
	let language: string | undefined;

	// For files that specify language via filename (name.language.ext).
	language ??= /(?<=[^./]*\.)[^./]*(?=\.[^./]*$)/.exec(filePath)?.[0];

	language ??= {
		".cpp": "cpp",
		".py": "python3",
	}[path.extname(filePath)];

	return language;
}

const memo: Record<string, typeof RunnerInterface> = {};
export function getConstructor(
	language: string
): typeof RunnerInterface | undefined {
	if (memo.hasOwnProperty(language)) return memo[language];

	const runnersPath = path.join(__dirname, "runners"),
		runnerPath = path.resolve(path.join(runnersPath, `${language}.${tj}s`));

	// existsSync probably isn't slow enough to necessitate this function being
	// asynchronous.
	if (path.dirname(runnerPath) != runnersPath || !fs.existsSync(runnerPath))
		return;

	return (memo[language] = require(runnerPath).default);
}

enum Code {
	INDETERMINATE_LANGUAGE = "INDETERMINATE_LANGUAGE",
	UNSUPPORTED_LANGUAGE = "UNSUPPORTED_LANGUAGE",
}
class CreateRunnerError extends Error {
	public static Code = Code;

	constructor(
		readonly code: Code,
		message: string,
		options?: ErrorOptions
	) {
		super(message, options);
	}
}

export function createRunner(
	filePath: string,
	{ language, ...options }: { language?: string } & RunnerOptions = {}
) {
	language ??= getLanguage(filePath);
	if (!language)
		throw new CreateRunnerError(
			CreateRunnerError.Code.INDETERMINATE_LANGUAGE,
			`Could not infer language of file: ${quote(filePath)}`
		);

	const Runner = getConstructor(language);
	if (!Runner)
		throw new CreateRunnerError(
			CreateRunnerError.Code.UNSUPPORTED_LANGUAGE,
			`Could not find runner for language: ${quote(language)}`
		);

	return new Runner(filePath, options);
}
