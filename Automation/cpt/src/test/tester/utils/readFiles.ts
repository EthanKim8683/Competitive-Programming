import fs from "fs";
import path from "path";

export default async (dirPath: string): Promise<Record<string, string>> => {
	const filePaths = await fs.promises.readdir(dirPath);
	const contents = await Promise.all(
		filePaths.map((filePath) =>
			fs.promises.readFile(path.join(dirPath, filePath))
		)
	);
	return Object.fromEntries(
		filePaths.map((filePath, index) => [
			path.parse(filePath).name,
			contents[index].toString(),
		])
	);
};
