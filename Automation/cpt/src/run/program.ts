import path from "path";

import { ProgramIniter, ProgramInvoker } from "./program/base";
import cpp from "./program/cpp";
import cpp17 from "./program/cpp17";
import cpp20 from "./program/cpp20";
import cpp23 from "./program/cpp23";
import python3 from "./program/python3";
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

	const program = {
		cpp,
		cpp17,
		cpp20,
		cpp23,
		python3,
	}[language];
	if (!program)
		return new ErrorProgramIniter(programPath, "Unsupported language", {
			cause: { language },
		});

	return program(programPath);
};
export default program;
