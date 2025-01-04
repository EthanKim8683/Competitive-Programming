import { ExecOptions, spawn, SpawnOptions } from "child_process";

import { Initer, Invoker, Process, ProcessError } from "../base";
import { NullReadable, NullWritable } from "../../lib/stream";

export class ProgramIniter extends Initer {}
export interface ProgramIniter extends Initer {
	readonly promise: Promise<ProgramInvoker>;
	readonly programPath: string;
}

export type ProgramInitOptions = {
	execOptions?: ExecOptions;
	cppOptions?: {
		std?: "c++98" | "c++03" | "c++11" | "c++14" | "c++17" | "c++20" | "c++23";
	};
};

export interface ProgramInvoker extends Invoker {
	readonly initer: ProgramIniter;

	invoke(options?: ProgramInvokeOptions): ProgramProcess;
}

export type ProgramInvokeOptions = {
	spawnOptions?: SpawnOptions;
};

export class ProgramProcess extends Process implements Process {
	readonly child;
	readonly stdin;
	readonly stdout;
	readonly stderr;
	private _abortController = new AbortController();

	constructor(
		readonly invoker: ProgramInvoker,
		command: string,
		args: string[] = [],
		{ spawnOptions = {} }: ProgramInvokeOptions = {}
	) {
		const { promise, resolve, reject } = Promise.withResolvers<void>();
		super(promise, () => this._abortController.abort());

		this.child = spawn(command, args, {
			...spawnOptions,
			signal: this._abortController.signal,
		});

		this.stdin = this.child.stdin ?? new NullWritable();
		this.stdout = this.child.stdout ?? new NullReadable();
		this.stderr = this.child.stderr ?? new NullReadable();

		this.child.on("exit", () => resolve());

		this.child.on("error", (err) => {
			if (err.name === "AbortError")
				return reject(
					new ProcessError(this, "Process aborted", { cause: err })
				);

			reject(err);
		});
	}
}

export interface ProgramModule {
	(programPath: string, options?: ProgramInitOptions): ProgramIniter;
}
