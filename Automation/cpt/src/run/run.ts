import { ChildProcess, spawn } from "child_process";
import { Readable, Writable } from "stream";

type Exit = {
	code: number | null;
	signal: NodeJS.Signals | null;
};

function run(
	args: string[],
	{
		stdin = process.stdin,
		stdout = process.stdout,
		stderr = process.stderr,
	}: { stdin?: Readable; stdout?: Writable; stderr?: Writable } = {}
): { child: ChildProcess; exit: Promise<Exit> } {
	if (args.length === 0) args = [""];
	const child = spawn(args[0], args.slice(1), {
		stdio: "pipe",
	});

	// Everything I/O can be handled with pipes. So, for the sake of
	// simplicity, I/O is all pipes.
	stdin.pipe(child.stdin!);
	child.stdout!.pipe(stdout);
	child.stderr!.pipe(stderr);

	const { promise, resolve, reject } = Promise.withResolvers<Exit>();

	child.on("error", (err) => reject(err));
	child.on("close", (code, signal) => resolve({ code, signal }));

	return { child, exit: promise };
}

export const partial =
	(args: string[]) => (options?: Parameters<typeof run>[1]) =>
		run(args, options);

export default run;
