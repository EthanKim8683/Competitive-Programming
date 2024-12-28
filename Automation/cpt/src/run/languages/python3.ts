import LanguageEntry from "../types/LanguageEntry";

const languageEntry: LanguageEntry = (filePath) => {
	return {
		spawnArgs: ["python3", filePath],
	};
};

export default languageEntry;
