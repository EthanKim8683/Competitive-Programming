import { LanguageEntry } from "../types";

const languageEntry: LanguageEntry = (filePath) => {
	return {
		spawnArgs: ["python3", filePath],
	};
};

export default languageEntry;
