import fs from "fs";
import parseIntWithError from "../../../utils/parseIntWithError";
import TesterTaskResult from "../types/TesterTaskResult";
import TesterInitTask from "../types/TesterInitTask";
import path from "path";

const readDir = async (
	dirPath: string,
	errorToSymbol: {
		default: string;
		accessError?: string;
	}
): Promise<TesterTaskResult<Record<number, string>>> =>
	fs.promises
		.readdir(dirPath)
		.then((filePaths) => {
			return {
				success: true as const,
				result: Object.fromEntries(
					filePaths.map((filePath) => [
						parseIntWithError(path.parse(filePath).name),
						path.join(dirPath, filePath),
					])
				),
			};
		})
		.catch((err) => {
			return {
				success: false,
				reasons: {
					[(
						{
							ENOENT: errorToSymbol.accessError,
							EACCES: errorToSymbol.accessError,
						} as Record<string, string | undefined>
					)[err.code] ?? errorToSymbol.default]: err,
				},
			};
		});
// Assert type
readDir as TesterInitTask<Record<number, string>>;
export default readDir;
