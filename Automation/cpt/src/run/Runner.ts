import fs from "fs";
import path from "path";
import { ChildProcess, execSync, spawn } from "child_process";
import { Readable, Writable } from "stream";
import { LanguageEntry } from "./types";
import NullReadable from "../stream/NullReadable";
import NullWritable from "../stream/NullWritable";
import quote from "../utils/quote";

function inferLanguage(filePath: string): string | undefined {
	let language: string | undefined;

	// For files that specify language via filename (name.language.ext),
	language ??= /(?<=[^./]*\.)[^./]*(?=\.[^./]*$)/.exec(filePath)?.[0];

	language ??= {
		".cpp": "c++20",
		".py": "python3",
	}[path.extname(filePath)];

	return language;
}

function getLanguageEntry(language: string): LanguageEntry | undefined {
	// No funny business. The language entry has to exist within the `languages`
	// directory.
	const languageEntriesPath = path.join(__dirname, "languages");
	const languageEntryPath = path.resolve(
		path.join(languageEntriesPath, `${language}.ts`)
	);
	if (
		path.dirname(languageEntryPath) === languageEntriesPath &&
		fs.existsSync(languageEntryPath)
	)
		return require(languageEntryPath).default;
}

function compileUsingArgs(args: string[]): string | undefined {
	return (
		execSync(
			// Basic sanitization for personal use. Just making sure I don't
			// accidentally hack myself.
			args.map((arg) => `"${arg.replaceAll(/[`"]/g, "\\$&")}"`).join(" ")
		).toString() || undefined
	);
}

function spawnUsingArgs(
	args: string[],
	{
		stdin = new NullReadable(),
		stdout = new NullWritable(),
		stderr = new NullWritable(),
	}: { stdin?: Readable; stdout?: Writable; stderr?: Writable } = {}
): ChildProcess {
	if (args.length === 0) args = [""];

	// Everything I/O can be handled with pipes. So, for the sake of simplicity,
	// I/O is forced to be all pipes.
	const child = spawn(args[0], args.slice(1), {
		stdio: "pipe",
	});
	stdin.pipe(child.stdin!);
	child.stdout!.pipe(stdout);
	child.stderr!.pipe(stderr);

	return child;
}

const spawnerUsingArgs =
	(args: string[]) => (stdio?: Parameters<typeof spawnUsingArgs>[1]) =>
		spawnUsingArgs(args, stdio);

export class RunnerConstructionError extends Error {
	constructor(
		readonly runner: Runner,
		message: string,
		options?: ErrorOptions
	) {
		super(message, options);
	}
}

export class RunnerRuntimeError extends Error {
	constructor(
		readonly runner: Runner,
		readonly pid: number,
		readonly code: number | null,
		readonly signal: NodeJS.Signals | null,
		options?: ErrorOptions
	) {
		super(
			signal
				? `${runner} killed with signal: '${signal}'`
				: `${runner} exited with non-zero exit code: '${code}'`,
			options
		);
	}
}

export default class Runner {
	readonly filePath: string;
	readonly language: string;
	readonly spawn: ReturnType<typeof spawnerUsingArgs>;

	constructor(filePath: string, language?: string) {
		fs.accessSync(filePath, fs.constants.R_OK);

		language ??= inferLanguage(filePath);
		if (!language)
			throw new RunnerConstructionError(
				this,
				`Could not infer language of file: ${quote(filePath)}`
			);

		const languageEntry = getLanguageEntry(language);
		if (!languageEntry)
			throw new RunnerConstructionError(
				this,
				`Unsupported language: ${quote(language)}`
			);
		const { compileArgs, spawnArgs } = languageEntry(filePath);

		if (compileArgs) compileUsingArgs(compileArgs);

		const spawn = spawnerUsingArgs(spawnArgs);

		this.filePath = filePath;
		this.language = language;
		this.spawn = spawn;
	}

	run(options?: Parameters<typeof this.spawn>[0]): Promise<void> {
		return new Promise<void>((resolve, reject) => {
			const child = this.spawn(options);

			child.on("exit", (code, signal) => {
				if (code || signal)
					reject(new RunnerRuntimeError(this, child.pid!, code, signal));
				resolve();
			});

			child.on("error", (err) => {
				if (!child.exitCode) child.kill();
				reject(err);
			});
		});
	}

	toString(): string {
		return `${quote(this.filePath)} (${this.language})`;
	}
}

export const makeRunner = async (
	filePath: string,
	language?: string
): Promise<Runner> => (async () => new Runner(filePath, language))();
