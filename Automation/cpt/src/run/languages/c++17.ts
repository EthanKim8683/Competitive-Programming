import tmp from "tmp";
import path from "path";
import { LanguageEntry } from "../types";

const languageEntry: LanguageEntry = (filePath) => {
	const { name: exePath } = tmp.fileSync();
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
		spawnArgs: [path.relative(process.cwd(), exePath)],
	};
};

export default languageEntry;
