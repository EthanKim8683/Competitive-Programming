import fs, { ReadStream } from "fs";
import path from "path";

import { KillablePromise } from "../utils/KillablePromise";
import { ContextfulError, isSystemError, Result } from "../utils/errors";

class ReadingDir extends KillablePromise<Result<ReadFile>> {
	private _fileNames?: string[];

	constructor(readonly dirPath: string) {
		const { promise, resolve, reject } =
			Promise.withResolvers<Result<ReadFile>>();
		super(promise);

		fs.readdir(dirPath, (err, files) => {
			if (err) {
				if (err.syscall === "scandir")
					return resolve({
						success: false,
						error: new ContextfulError(
							"Could not read directory",
							{ dirPath },
							{ cause: err }
						),
					});

				return reject(err);
			}

			this._fileNames = files;
			resolve({
				success: true,
				result: (fileName: string): Result<ReadingFile> => {
					if (!files.includes(fileName))
						return {
							success: false,
							error: new ContextfulError(
								"Provided file name is not among those present in directory",
								{ fileName, allowedFileNames: files }
							),
						};

					return { success: true, result: new ReadingFile(this, fileName) };
				},
			});
		});
	}

	get fileNames() {
		return this._fileNames;
	}
}

type ReadFile = (fileName: string) => Result<ReadingFile>;

class ReadingFile extends KillablePromise<Result<void>> {
	readonly stream: ReadStream;

	constructor(readingDir: ReadingDir, fileName: string) {
		const { promise, resolve, reject } = Promise.withResolvers<Result<void>>();
		const abortController = new AbortController();
		super(promise, () => abortController.abort());

		const filePath = path.join(readingDir.dirPath, fileName);
		this.stream = fs.createReadStream(filePath, {
			signal: abortController.signal,
		});

		this.stream.on("close", () =>
			resolve({ success: true, result: undefined })
		);

		this.stream.on("error", (err) => {
			if (isSystemError(err) && err.syscall === "open")
				return resolve({
					success: false,
					error: new ContextfulError(
						"Could not open file",
						{ filePath },
						{ cause: err }
					),
				});

			reject(err);
		});
	}
}

export default (dirPath: string) => new ReadingDir(dirPath);
