import path from "path";

import { quote } from "../util";
import { EntryInterface, InitOptions } from "./base";
import entries from "./entries";

export function getLanguage(filePath: string): string | undefined {
	let language: string | undefined;

	// For directories
	language ??= /(?:^|\/)[^\/.]+$/.test(filePath) ? "dir" : undefined;

	// For files that specify language via filename (name.language.ext).
	language ??= /(?<=[^./]*\.)[^./]*(?=\.[^./]*$)/.exec(filePath)?.[0];

	language ??= {
		".cpp": "cpp",
		".py": "python3",
	}[path.extname(filePath)];

	return language;
}

export function getEntry(language: string): EntryInterface | undefined {
	if (entries.hasOwnProperty(language)) return entries[language];
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
	{ language, ...options }: { language?: string } & InitOptions = {}
) {
	language ??= getLanguage(filePath);
	if (!language)
		throw new CreateRunnerError(
			CreateRunnerError.Code.INDETERMINATE_LANGUAGE,
			`Could not infer language of file: ${quote(filePath)}`
		);

	const entry = getEntry(language);
	if (!entry)
		throw new CreateRunnerError(
			CreateRunnerError.Code.UNSUPPORTED_LANGUAGE,
			`Could not find runner for language: ${quote(language)}`
		);

	return entry(filePath, options);
}
