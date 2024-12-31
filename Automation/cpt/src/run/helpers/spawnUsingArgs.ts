import { spawn, ChildProcess } from "child_process";
import { Readable, Writable } from "stream";
import NullReadable from "../../stream/NullReadable";
import NullWritable from "../../stream/NullWritable";

export default (
	args: string[],
	{
		stdin = new NullReadable(),
		stdout = new NullWritable(),
		stderr = new NullWritable(),
	}: { stdin?: Readable; stdout?: Writable; stderr?: Writable } = {}
): ChildProcess => {
	if (args.length === 0) args = [""];

	// Everything I/O can be handled with pipes. So, for the sake of simplicity,
	// I/O is forced to be all pipes.
	const child = spawn(args[0], args.slice(1), {
		stdio: "pipe",
	});
	if (child.stdin) stdin.pipe(child.stdin);
	if (child.stdout) child.stdout.pipe(stdout);
	if (child.stderr) child.stderr.pipe(stderr);

	return child;
};
