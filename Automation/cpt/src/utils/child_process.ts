import cp, { ChildProcess, ExecOptions } from "child_process";

// Basic sanitization and spawn-like syntax
export const exec = (
	command: string,
	args: string[],
	options?: ExecOptions,
	callback?: Parameters<typeof cp.exec>[2]
): ChildProcess =>
	cp.exec(
		[command, ...args]
			.map((arg) => `"${arg.replaceAll(/[`"]/g, "\\$&")}"`)
			.join(" "),
		options,
		callback
	);
