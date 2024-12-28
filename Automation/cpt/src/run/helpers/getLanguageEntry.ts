import path from "path";
import fs from "fs";
import LanguageEntry from "../types/LanguageEntry";

export default (language: string): LanguageEntry | undefined => {
	// No funny business. The language entry has to exist within the `languages`
	// directory.
	const languageEntriesPath = path.join(__dirname, "languages");
	const languageEntryPath = path.resolve(
		path.join(languageEntriesPath, `${language}.ts`)
	);
	if (
		path.dirname(languageEntryPath) === languageEntriesPath &&
		fs.existsSync(languageEntryPath)
	)
		return require(languageEntryPath).default;
};
