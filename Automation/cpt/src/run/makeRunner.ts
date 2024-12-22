import fs from "fs";
import path from "path";
import { LanguageEntry } from "./types";

const languageEntries: Record<string, LanguageEntry> = {};

export default async (
	filePath: string,
	language?: string
): ReturnType<LanguageEntry> => {
	if (!fs.existsSync(filePath))
		return { success: false, error: `could not find file \`${filePath}\`` };

	if (!language)
		language = /(?<=[^./]*\.)[^./]*(?=\.[^./]*)/.exec(filePath)?.[0];

	if (!language)
		language = {
			".cpp": "c++20",
		}[path.extname(filePath)];

	if (!language)
		return {
			success: false,
			error: `could not determine language of file \`${filePath}\``,
		};

	let languageEntry;
	if (languageEntries.hasOwnProperty(language))
		languageEntry = languageEntries[language];
	else {
		const languageEntryPath = path.join(
			__dirname,
			"languages",
			`${language}.ts`
		);
		if (!fs.existsSync(languageEntryPath))
			return { success: false, error: `unsupported language \`${language}\`` };
		languageEntry = require(languageEntryPath).default;
	}

	return languageEntry(filePath);
};
