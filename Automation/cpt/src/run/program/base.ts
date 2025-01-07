import { ChildProcess, spawn, SpawnOptions } from "child_process";
import { Readable, Writable } from "stream";

import { ExitStatus, Initer, Invoker, Process } from "../base";
import { NullReadable, NullWritable } from "../../lib/stream";

export class ProgramIniter<
	T extends ProgramInvoker = ProgramInvoker,
> extends Initer<T> {}
export interface ProgramIniter<T extends ProgramInvoker = ProgramInvoker>
	extends Initer<T> {
	readonly programPath: string;
}

export interface ProgramInvoker extends Invoker {
	readonly initer: ProgramIniter;

	invoke(options?: SpawnOptions): ProgramProcess;
}

export class ProgramProcess extends Process implements Process {
	readonly child: ChildProcess;
	readonly stdin: Writable;
	readonly stdout: Readable;
	readonly stderr: Readable;
	private _abortController = new AbortController();

	constructor(
		readonly invoker: ProgramInvoker,
		command: string,
		args: string[] = [],
		options: SpawnOptions = {}
	) {
		const { promise, resolve, reject } = Promise.withResolvers<ExitStatus>();
		super(promise, () => this._abortController.abort());

		this.child = spawn(command, args, {
			...options,
			signal: this._abortController.signal,
		});

		this.stdin = this.child.stdin ?? new NullWritable();
		this.stdout = this.child.stdout ?? new NullReadable();
		this.stderr = this.child.stderr ?? new NullReadable();

		this.child.on("exit", (exitCode, signalCode) =>
			resolve({ exitCode, signalCode })
		);

		this.child.on("error", (err) => {
			if (err.name === "AbortError")
				return resolve({ exitCode: null, signalCode: "SIGABRT" });

			reject(err);
		});
	}
}

export interface ProgramModule {
	(programPath: string): ProgramIniter;
}
