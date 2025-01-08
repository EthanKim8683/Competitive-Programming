import path from "path";
import fs from "fs";

import { ProgramIniter, ProgramInvoker, ProgramModule } from "./program/base";
import { InitError } from "./base";

export function getLanguage(programPath: string): string | undefined {
	let language: string | undefined;

	// For files that specify language via filename (name.language.ext).
	language ??= /(?<=[^./]*\.)[^./]*(?=\.[^./]*$)/.exec(programPath)?.[0];

	language ??= {
		".cpp": "cpp",
		".py": "python3",
	}[path.extname(programPath)];

	return language;
}

const cache: Record<string, ProgramModule> = {};
export function getProgramModule(language: string): ProgramModule | undefined {
	if (cache.hasOwnProperty(language)) return cache[language];

	const programDirPath = path.join(__dirname, "program"),
		programModulePath = path.join(programDirPath, `${language}.ts`);
	if (
		path.normalize(programDirPath) !==
			path.normalize(path.dirname(programModulePath)) ||
		!fs.existsSync(programModulePath)
	)
		return;

	return (cache[language] = require(programModulePath));
}

class ErrorProgramIniter extends ProgramIniter implements ProgramIniter {
	constructor(
		readonly programPath: string,
		message: string,
		options?: ErrorOptions
	) {
		const { promise, reject } = Promise.withResolvers<ProgramInvoker>();
		super(promise);
		reject(new InitError(this, message, options));
	}
}

const program = (
	programPath: string,
	language?: string
): ProgramIniter<ProgramInvoker> => {
	language ??= getLanguage(programPath);
	if (!language)
		return new ErrorProgramIniter(
			programPath,
			"Could not infer language from filename",
			{ cause: { filename: programPath } }
		);

	const programModule = getProgramModule(language);
	if (!programModule)
		return new ErrorProgramIniter(programPath, "Unsupported language", {
			cause: { language },
		});

	return programModule(programPath);
};
export default program;
