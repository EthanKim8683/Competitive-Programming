import { spawn } from "child_process";
import tmp from "tmp";
import fs from "fs/promises";
import { StdioOption, StdinOption, StdoutOption, StderrOption } from "./types";
import { Readable, Writable } from "stream";

function stdioOptionToSpawnStdioOption(stdioOption: StdioOption) {
	switch (stdioOption) {
		case StdioOption.STRING:
			return "pipe";
		case StdioOption.INHERIT:
			return "inherit";
		case StdioOption.IGNORE:
			return "ignore";
	}
}

type Options<
	T0 extends StdinOption | undefined,
	T1 extends StdoutOption | undefined,
	T2 extends StderrOption | undefined,
> = {
	stdin?: T0;
	stdout?: T1;
	stderr?: T2;
	aborter?: AbortController;
};

type ExecutionResult<
	T1 extends StdoutOption,
	T2 extends StderrOption,
> = Promise<{
	code: number | null;
	signal: NodeJS.Signals | null;
	stdout: T1 extends StdioOption.STRING ? string : null;
	stderr: T2 extends StdioOption.STRING ? string : null;
	time: number;
	memory: number;
}>;

function execute<
	T0 extends StdinOption = StdioOption.INHERIT,
	T1 extends StdoutOption = StdioOption.INHERIT,
	T2 extends StderrOption = StdioOption.INHERIT,
>(args: string[], options?: Options<T0, T1, T2>): ExecutionResult<T1, T2>;

function execute(
	args: string[]
): ExecutionResult<StdioOption.STRING, StdioOption.STRING>;

function execute(
	args: string[],
	{
		stdin: stdinOption = StdioOption.INHERIT,
		stdout: stdoutOption = StdioOption.INHERIT,
		stderr: stderrOption = StdioOption.INHERIT,
		aborter,
	}: Options<
		StdinOption | undefined,
		StdoutOption | undefined,
		StderrOption | undefined
	> = {}
) {
	return new Promise((resolve, reject) => {
		tmp.file((err, rusagePath) => {
			if (err) return reject(err);

			const child = spawn("/usr/bin/time", ["-l", "-o", rusagePath, ...args], {
				stdio: [
					typeof stdinOption === "string" || stdinOption instanceof Readable
						? "pipe"
						: "inherit",
					stdoutOption === StdioOption.STRING ||
					stdoutOption instanceof Writable
						? "pipe"
						: stdioOptionToSpawnStdioOption(stdoutOption),
					stderrOption === StdioOption.STRING ||
					stderrOption instanceof Writable
						? "pipe"
						: stdioOptionToSpawnStdioOption(stderrOption),
				],
				signal: aborter?.signal,
			});

			{
				if (typeof stdinOption === "string")
					child.stdin!.write(`${stdinOption}\n`);

				if (stdinOption instanceof Readable) stdinOption.pipe(child.stdin!);
			}

			let stdout = "";
			{
				if (stdoutOption === StdioOption.STRING)
					child.stdout!.on("data", (data) => (stdout += data));

				if (stdoutOption instanceof Writable) child.stdout!.pipe(stdoutOption);
			}

			let stderr = "";
			{
				if (stderrOption === StdioOption.STRING)
					child.stderr!.on("data", (data) => (stderr += data));

				if (stderrOption instanceof Writable) child.stderr!.pipe(stderrOption);
			}

			child.on("error", (err) =>
				reject(`child process became unresponsive:\n${err}`)
			);

			child.on("close", async (code, signal) => {
				const rusage = await fs
					.readFile(rusagePath)
					.then((buffer) => buffer.toString());

				const userMatch = /\d+\.\d+(?=\s+user)/.exec(rusage);
				const sysMatch = /\d+\.\d+(?=\s+sys)/.exec(rusage);
				const maxrssMatch = /\d+(?=\s+maximum resident set size)/.exec(rusage);
				if (!userMatch || !sysMatch || !maxrssMatch)
					return reject(`could not parse rusage:\n${rusage}`);

				resolve({
					code,
					signal,
					stdout: stdoutOption === StdioOption.STRING ? stdout : null,
					stderr: stderrOption === StdioOption.STRING ? stderr : null,
					time: parseFloat(userMatch[0]) + parseFloat(sysMatch[0]),
					memory: parseInt(maxrssMatch[0]),
				});
			});
		});
	});
}

export function makeExecutor(args: string[]) {
	return <
		T0 extends StdinOption,
		T1 extends StdoutOption,
		T2 extends StderrOption,
	>(options?: {
		stdin?: T0;
		stdout?: T1;
		stderr?: T2;
		aborter?: AbortController;
	}) => execute<T0, T1, T2>(args, options);
}

export default execute;
