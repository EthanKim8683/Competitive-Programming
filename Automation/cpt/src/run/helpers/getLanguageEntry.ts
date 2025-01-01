import path from "path";
import fs from "fs";
import LanguageEntry from "../types/LanguageEntry";

const languageEntries: Record<string, LanguageEntry> = {};
export default (language: string): LanguageEntry | undefined => {
	if (languageEntries.hasOwnProperty(language))
		return languageEntries[language];

	// No funny business. The language entry has to exist within the `languages`
	// directory.
	const languageEntriesPath = path.join(__dirname, "../languages");
	const languageEntryPath = path.resolve(
		path.join(languageEntriesPath, `${language}.ts`)
	);
	if (
		path.dirname(languageEntryPath) === languageEntriesPath &&
		fs.existsSync(languageEntryPath)
	)
		return (languageEntries[language] = require(languageEntryPath).default);
};
