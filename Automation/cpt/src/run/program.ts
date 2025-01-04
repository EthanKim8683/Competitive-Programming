import path from "path";

import { ProgramIniter, ProgramInitOptions } from "./program/base";
import cpp from "./program/cpp";
import cpp17 from "./program/cpp17";
import cpp20 from "./program/cpp20";
import cpp23 from "./program/cpp23";
import python3 from "./program/python3";

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

const program = (
	programPath: string,
	{ language, ...options }: { language?: string } & ProgramInitOptions = {}
): ProgramIniter => {
	language ??= getLanguage(programPath);
	if (!language) throw "";

	const program = {
		cpp,
		cpp17,
		cpp20,
		cpp23,
		python3,
	}[language];
	if (!program) throw "";

	return program(programPath, options);
};
export default program;
