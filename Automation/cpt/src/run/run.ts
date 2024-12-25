import { spawn } from "child_process";
import tmp from "tmp";
import fs from "fs/promises";
import { Readable, Writable } from "stream";

function run(
	args: string[],
	{
		stdin = process.stdin,
		stdout = process.stdout,
		stderr = process.stderr,
	}: { stdin?: Readable; stdout?: Writable; stderr?: Writable } = {}
): Promise<{
	code: number | null;
	signal: NodeJS.Signals | null;
	time: number;
	memory: number;
}> {
	return new Promise((resolve, reject) => {
		tmp.file((err, rusagePath) => {
			if (err) return reject(err);

			const child = spawn("/usr/bin/time", ["-l", "-o", rusagePath, ...args], {
				stdio: "pipe",
			});

			stdin.pipe(child.stdin!);
			child.stdout!.pipe(stdout);
			child.stderr!.pipe(stderr);

			child.on("error", (err) => {
				reject(`child process error:\n${err}`);
			});

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
					time: parseFloat(userMatch[0]) + parseFloat(sysMatch[0]),
					memory: parseInt(maxrssMatch[0]),
				});
			});
		});
	});
}

export const partial =
	(args: string[]) => (options?: Parameters<typeof run>[1]) =>
		run(args, options);

export default run;
