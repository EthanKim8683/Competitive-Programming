import { spawn } from "child_process";
import tmp from "tmp";
import fs from "fs/promises";
import { StdioOption, StdinOption, StdoutOption, StderrOption } from "./types";
import { Readable, Writable } from "stream";
import { IfIncludes } from "../utils/types";

type Options<
	T0 extends StdinOption | undefined,
	T1 extends StdoutOption[] | undefined,
	T2 extends StderrOption[] | undefined,
> = {
	stdin?: T0;
	stdout?: T1;
	stderr?: T2;
	aborter?: AbortController;
};

type ExecutionResult<
	T1 extends StdoutOption[],
	T2 extends StderrOption[],
> = Promise<{
	code: number | null;
	signal: NodeJS.Signals | null;
	stdout: IfIncludes<T1, StdioOption.STRING, string, null>;
	stderr: IfIncludes<T2, StdioOption.STRING, string, null>;
	time: number;
	memory: number;
}>;

function execute<
	T0 extends StdinOption = StdioOption.INHERIT,
	T1 extends StdoutOption[] = [StdioOption.INHERIT],
	T2 extends StderrOption[] = [StdioOption.INHERIT],
>(args: string[], options?: Options<T0, T1, T2>): ExecutionResult<T1, T2>;

function execute(
	args: string[]
): ExecutionResult<[StdioOption.INHERIT], [StdioOption.INHERIT]>;

function execute(
	args: string[],
	{
		stdin: stdinOption = StdioOption.INHERIT,
		stdout: stdoutOptions = [StdioOption.INHERIT],
		stderr: stderrOptions = [StdioOption.INHERIT],
		aborter,
	}: Options<
		StdinOption | undefined,
		StdoutOption[] | undefined,
		StderrOption[] | undefined
	> = {}
) {
	return new Promise((resolve, reject) => {
		tmp.file((err, rusagePath) => {
			if (err) return reject(err);

			const stdinString =
				typeof stdinOption === "string" && stdinOption.length > 0;
			const stdinInherit = stdinOption === StdioOption.INHERIT;
			const stdinPipe = stdinOption instanceof Readable;

			const stdoutString = stdoutOptions.includes(StdioOption.STRING);
			const stdoutInherit = stdoutOptions.includes(StdioOption.INHERIT);
			const stdoutPipes = stdoutOptions.filter(
				(option) => option instanceof Writable
			);

			const stderrString = stderrOptions.includes(StdioOption.STRING);
			const stderrInherit = stderrOptions.includes(StdioOption.INHERIT);
			const stderrPipes = stderrOptions.filter(
				(option) => option instanceof Writable
			);

			const stdoutSpawnOption =
				stdoutString || stdoutPipes.length > 0
					? "pipe"
					: stdoutInherit
						? "inherit"
						: "ignore";

			const stderrSpawnOption =
				stderrString || stderrPipes.length > 0
					? "pipe"
					: stderrInherit
						? "inherit"
						: "ignore";

			const child = spawn("/usr/bin/time", ["-l", "-o", rusagePath, ...args], {
				stdio: [
					stdinString || stdinPipe
						? "pipe"
						: stdinInherit
							? "inherit"
							: "ignore",
					stdoutSpawnOption,
					stderrSpawnOption,
				],
				signal: aborter?.signal,
			});

			if (stdinString) child.stdin!.write(`${stdinOption}\n`);

			if (stdinPipe) stdinOption.pipe(child.stdin!);

			let stdout = "";
			if (stdoutString) child.stdout!.on("data", (data) => (stdout += data));

			if (stdoutPipes.length > 0)
				stdoutPipes.forEach((option) => child.stdout!.pipe(option));

			if (stdoutInherit && stdoutSpawnOption === "pipe")
				child.stdout!.pipe(process.stdout);

			let stderr = "";
			if (stderrString) child.stderr!.on("data", (data) => (stderr += data));

			if (stderrPipes.length > 0)
				stderrPipes.forEach((option) => child.stderr!.pipe(option));

			if (stderrInherit && stderrSpawnOption === "pipe")
				child.stderr!.pipe(process.stderr);

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
					stdout: stdoutOptions.includes(StdioOption.STRING) ? stdout : null,
					stderr: stderrOptions.includes(StdioOption.STRING) ? stderr : null,
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
		T1 extends StdoutOption[],
		T2 extends StderrOption[],
	>(options?: {
		stdin?: T0;
		stdout?: T1;
		stderr?: T2;
		aborter?: AbortController;
	}) => execute<T0, T1, T2>(args, options);
}

export default execute;
