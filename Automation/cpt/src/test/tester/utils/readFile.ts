import { Writable } from "stream";
import fs from "fs";
import TesterRunTask from "../types/TesterRunTask";
import TesterTaskResult from "../types/TesterTaskResult";
import isSystemError from "../../../utils/isSystemError";

const readFile = (
	[filePath, stdout]: [string, Writable | undefined],
	errorToSymbol: { default: string; accessError?: string }
): {
	promise: Promise<TesterTaskResult<undefined>>;
	kill: () => void;
} => {
	const abortController = new AbortController();
	return {
		promise: new Promise<TesterTaskResult<undefined>>((resolve, reject) => {
			const stream = fs.createReadStream(filePath, {
				signal: abortController.signal,
			});
			if (stdout) stream.pipe(stdout);

			stream.on("error", (err) => {
				if (!isSystemError(err)) return reject(err);

				resolve({
					success: false,
					reasons: {
						[(
							{
								ENOENT: errorToSymbol.accessError,
								EACCES: errorToSymbol.accessError,
							} as Record<string, string | undefined>
						)[err.code] ?? errorToSymbol.default]: err,
					},
				});
			});

			stream.on("close", () => {
				resolve({ success: true, result: undefined });
			});
		}),
		kill: () => abortController.abort(),
	};
};
readFile as TesterRunTask<undefined>;
export default readFile;
