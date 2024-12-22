import makeLanguageEntry from "../makeLanguageEntry";

export default makeLanguageEntry(async (filePath) => {
	return {
		execute: ["python3", filePath],
	};
});
