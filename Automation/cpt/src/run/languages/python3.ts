import { LanguageEntry } from "../types";

const languageEntry: LanguageEntry = (filePath) => {
	return {
		runArgs: ["python3", filePath],
	};
};

export default languageEntry;
