import fs from "fs";
import path from "path";
import { MakeRunnerResult } from "./types";
import compile from "./compile";
import { partial } from "./run";
import { LanguageEntry } from "./types";

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
	const accessError = await fs.promises
		.access(filePath, fs.constants.R_OK)
		.catch((err: Error) => err.toString());
	if (accessError)
		return {
			success: false,
			error: accessError,
		};

	if (!(language = inferLanguage(filePath, language)))
		return {
			success: false,
			error: `Could not infer language of file: \`${filePath}\``,
		};

	const languageEntry = getLanguageEntry(language);
	if (!languageEntry)
		return {
			success: false,
			error: `Unsupported language: \`${language}\``,
		};
	const args = await languageEntry(filePath);
	const { compileArgs, runArgs } = args;

	let warning: string | undefined;
	if (compileArgs) {
		const compileResult = await compile(compileArgs);
		if (!compileResult.success)
			return {
				success: false,
				error: compileResult.error,
			};
		else ({ warning } = compileResult);
	}

	return {
		success: true,
		warning,
		run: partial(runArgs),
	};
};
