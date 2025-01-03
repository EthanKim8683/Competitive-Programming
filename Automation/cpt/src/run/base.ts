import { ExecOptions, SpawnOptions } from "child_process";

import { KillablePromise } from "../base";

// Options for a variety of initers or runners can be provided and the instance
// will pick which ones to interpret.
//
// For further control over InitOptions, use instanceof to determine the
// relevant class first.
export type InitOptions = {
	// If init uses exec:
	execOptions?: ExecOptions;
	// If initer is CppIniter-like:
	cppOptions?: {
		// g++-14 -std= option:
		std?: "c++98" | "c++03" | "c++11" | "c++14" | "c++17" | "c++20" | "c++23";
	};
};
export type RunOptions = {
	// If run uses spawn:
	spawnOptions?: SpawnOptions;
	// If runner is DirRunner:
	dirOptions?: {
		// Name of file, excluding dirname:
		basename?: string;
	};
};

export class InitError extends Error {
	constructor(
		readonly initer: IniterInterface,
		message: string,
		options?: ErrorOptions
	) {
		super(message, options);
	}
}

export interface IniterInterface extends KillablePromise<RunnerInterface> {
	readonly filePath: string;
}

export interface RunnerInterface {
	readonly initer: IniterInterface;

	run(options?: RunOptions): ProcessInterface;
}

export interface ProcessInterface extends KillablePromise<ProcessInterface> {}

export interface EntryInterface {
	(filePath: string, options?: InitOptions): IniterInterface;
}
