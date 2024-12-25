import tmp from "tmp-promise";
import path from "path";
import { LanguageEntry } from "../types";

const languageEntry: LanguageEntry = async (filePath) => {
	const { path: exePath } = await tmp.file();
	return {
		compileArgs: [
			"/opt/homebrew/bin/g++-14",
			"-o",
			exePath,
			filePath,
			"-O2",
			"-DETHANKIM8683",
			"-std=c++17",
		],
		runArgs: [path.relative(process.cwd(), exePath)],
	};
};

export default languageEntry;
