import fs from "fs";
import path from "path";
import { LanguageEntry, MakeRunnerError, MakeRunnerResult } from "./types";
import compile from "./compile";
import { partial } from "./run";

function inferLanguage(
	filePath: string,
	language?: string
): string | undefined {
	if (!language)
		language = /(?<=[^./]*\.)[^./]*(?=\.[^./]*$)/.exec(filePath)?.[0];

	if (!language)
		language = {
			".cpp": "c++20",
			".py": "python3",
		}[path.extname(filePath)];

	return language;
}

const languageEntries: Record<string, LanguageEntry> = {};
function getLanguageEntry(language: string): LanguageEntry | undefined {
	if (languageEntries.hasOwnProperty(language))
		return languageEntries[language];

	const languageEntryPath = path.join(__dirname, "languages", `${language}.ts`);
	if (!fs.existsSync(languageEntryPath)) return;

	return (languageEntries[language] = require(languageEntryPath).default);
}

export default async (
	filePath: string,
	language?: string
): Promise<MakeRunnerResult> => {
	const base = {
		filePath,
	};

	const accessError = await fs.promises
		.access(filePath, fs.constants.R_OK)
		.catch((err: Error) => err.toString());
	if (accessError)
		return {
			...base,
			success: false,
			error: MakeRunnerError.ACCESS_ERROR,
			hint: accessError,
		};

	const accessed = {
		...base,
	};

	if (!(language = inferLanguage(filePath, language)))
		return {
			...accessed,
			success: false,
			error: MakeRunnerError.INFER_ERROR,
		};

	const inferred = {
		...accessed,
		language,
	};

	const languageEntry = getLanguageEntry(language);
	if (!languageEntry)
		return {
			...inferred,
			success: false,
			error: MakeRunnerError.SUPPORT_ERROR,
		};
	const args = await languageEntry(filePath);
	const { compileArgs, runArgs } = args;

	const supports = {
		...inferred,
		...args,
	};

	let warning: string | undefined;
	if (compileArgs) {
		const compileResult = await compile(compileArgs);
		if (!compileResult.success)
			return {
				...supports,
				success: false,
				error: MakeRunnerError.COMPILE_ERROR,
				hint: compileResult.error,
			};
		else ({ warning } = compileResult);
	}

	const compiled = {
		...supports,
		warning,
		run: partial(runArgs),
	};

	return {
		...compiled,
		success: true,
	};
};
