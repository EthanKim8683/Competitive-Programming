import fs from "fs";
import path from "path";
import parseIntWithError from "../../../utils/parseIntWithError";
import TesterInitResult from "../types/TesterInitResult";
import TesterInitTask from "../types/TesterInitTask";

const readFiles = async (
	dirPath: string,
	errorToSymbol: {
		default: string;
		dirAccessError?: string;
		fileAccessError?: string;
		fileNameError?: string;
	}
): Promise<TesterInitResult<Record<number, string>>> => {
	const contents: string[] = [],
		reasons: Record<string, Error | Error[]> = {};

	const filePaths = await fs.promises.readdir(dirPath).catch((err) => {
		errorSymbols.push(
			(
				{
					ENOENT: errorToSymbol.dirAccessError,
					EACCES: errorToSymbol.dirAccessError,
				} as Record<string, string | undefined>
			)[err.code] ?? errorToSymbol.default
		);
		reasons.push(err);
		return [];
	});
	const keys = filePaths.map((filePath) =>
		parseIntWithError(path.parse(filePath).name)
	);

	const outcomes = await Promise.allSettled(
		filePaths.map((filePath) =>
			fs.promises.readFile(path.join(dirPath, filePath))
		)
	);
	for (const outcome of outcomes) {
		if (outcome.status === "fulfilled") contents.push(outcome.value.toString());
		else {
			const err = outcome.reason;
			errorSymbols.push(
				(
					{
						ENOENT: errorToSymbol.fileAccessError,
						EACCES: errorToSymbol.fileAccessError,
					} as Record<string, string | undefined>
				)[err.code] ?? errorToSymbol.default
			);
			reasons.push(err);
		}
	}

	if (reasons.length > 0)
		return {
			success: false,
			errorSymbols,
			reasons,
		};
	else
		return {
			success: true,
			result: Object.fromEntries(
				keys.map((key, index) => [key, contents[index].toString()])
			),
		};
};
// Assert type
readFiles as TesterInitTask<Record<number, string>>;
export default readFiles;
