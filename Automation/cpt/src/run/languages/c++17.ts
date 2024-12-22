import tmp from "tmp-promise";
import path from "path";
import makeLanguageEntry from "../makeLanguageEntry";

export default makeLanguageEntry(async (filePath) => {
	const { path: exePath } = await tmp.file();
	return {
		compile: [
			"/opt/homebrew/bin/g++-14",
			"-o",
			exePath,
			filePath,
			"-O2",
			"-DETHANKIM8683",
			"-std=c++17",
		],
		execute: [path.relative(process.cwd(), exePath)],
	};
});
