import { Readable, Writable } from "stream";
import { spawn, SpawnOptions } from "child_process";
import path from "path";

import { KillablePromise } from "../utils/KillablePromise";
import { exec } from "../utils/child_process";
import { absolute } from "../utils/path";
import { NullReadable, NullWritable } from "../utils/stream";
import { ContextfulError, Result } from "../utils/errors";

const compilePath = path.join(__dirname, "../../../cnr/compile.sh");
class Compilation extends KillablePromise<Result<Runner>> {
	private _executablePath?: string;
	private _compilerWarning?: string;

	constructor(
		readonly programPath: string,
		language?: string
	) {
		const { promise, resolve, reject } =
			Promise.withResolvers<Result<Runner>>();
		const abortController = new AbortController();
		super(promise, () => abortController.abort());

		const { dir, name } = path.parse(absolute(programPath));
		const executablePath = path.join(dir, name);

		const args = [programPath, executablePath];
		if (language) args.push(language);

		const child = exec(
			compilePath,
			args,
			{ signal: abortController.signal },
			(error, _stdout, stderr) => {
				if (error) {
					if (error.name === "AbortError")
						return resolve({
							success: false,
							error: new Error("Compilation aborted", { cause: error }),
						});

					if (child.exitCode !== 0)
						return resolve({
							success: false,
							error: new ContextfulError(
								"Compilation exited with non-zero exit code",
								{ exitCode: child.exitCode }
							),
						});

					if (child.signalCode !== null)
						return resolve({
							success: false,
							error: new ContextfulError("Compilation terminated", {
								signalCode: child.signalCode,
							}),
						});

					return reject(error);
				}

				this._executablePath = executablePath;
				this._compilerWarning = stderr.toString("utf8");
				resolve({
					success: true,
					result: (options: SpawnOptions = {}) => new Process(this, options),
				});
			}
		);
	}

	get executablePath() {
		return this._executablePath;
	}

	get compilerWarning() {
		return this._compilerWarning;
	}
}

type Runner = (options?: SpawnOptions) => Process;

// Based on shell processes
class Process extends KillablePromise<ExitStatus> {
	readonly stdin: Writable;
	readonly stdout: Readable;
	readonly stderr: Readable;

	constructor(compilation: Compilation, options: SpawnOptions = {}) {
		const { promise, resolve, reject } = Promise.withResolvers<ExitStatus>();
		const abortController = new AbortController();
		super(promise, () => abortController.abort());

		const child = spawn(compilation.executablePath!, [], {
			...options,
			signal: abortController.signal,
		});

		this.stdin = child.stdin ?? new NullWritable();
		this.stdout = child.stdout ?? new NullReadable();
		this.stderr = child.stderr ?? new NullReadable();

		child.on("exit", (exitCode, signalCode) =>
			resolve({ exitCode, signalCode })
		);

		child.on("error", (err) => {
			if (err.name === "AbortError")
				return resolve({ exitCode: null, signalCode: "SIGABRT" });

			reject(err);
		});
	}
}

type ExitStatus = {
	exitCode: number | null;
	signalCode: NodeJS.Signals | null;
};

export default (programPath: string, language?: string) =>
	new Compilation(programPath, language);
