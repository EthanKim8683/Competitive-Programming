import fs from "fs";
import path from "path";
import parseIntWithError from "../../../utils/parseIntWithError";

export default async (dirPath: string): Promise<Record<number, string>> => {
	const filePaths = await fs.promises.readdir(dirPath);
	const keys = filePaths.map((filePath) =>
		parseIntWithError(path.parse(filePath).name)
	);
	const contents = await Promise.all(
		filePaths.map((filePath) =>
			fs.promises.readFile(path.join(dirPath, filePath))
		)
	);
	return Object.fromEntries(
		keys.map((key, index) => [key, contents[index].toString()])
	);
};
