import { ExecOptions, SpawnOptions } from "child_process";

import { KillablePromise } from "../base";

// Remember, language-specific options should be prefixed by the name of the
// corresponding language (e.g. cppStd).
export type InitOptions = {
	execOptions?: ExecOptions;
	cppStd?: "c++98" | "c++03" | "c++11" | "c++14" | "c++17" | "c++20" | "c++23";
};
export type RunOptions = {
	spawnOptions?: SpawnOptions;
	dirBasename?: string;
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
