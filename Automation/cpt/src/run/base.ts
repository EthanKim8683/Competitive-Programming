import { ExecOptions, spawn, SpawnOptions } from "child_process";

// Remember, language-specific options should be prefixed by the name of the
// corresponding language (e.g. cppStd).
export type RunOptions = Pick<SpawnOptions, "timeout" | "stdio">;
export type IniterOptions = Pick<ExecOptions, "timeout"> & {
	cppStd?: "c++98" | "c++03" | "c++11" | "c++14" | "c++17" | "c++20" | "c++23";
};

export class Run {
	readonly child;
	readonly promise;
	private _abortController = new AbortController();
	private _settled = false;

	constructor(command: string, args: string[] = [], options: RunOptions = {}) {
		this.child = spawn(command, args, {
			...options,
			signal: this._abortController.signal,
		});
		this.promise = new Promise<Run>((resolve, reject) => {
			this.child.on("exit", () => {
				this._settled = true;
				resolve(this);
			});

			this.child.on("error", (err) => {
				// AbortErrors aren't real errors. We already know the process has been
				// aborted because we aborted it.
				if (err.name === "AbortError") return;
				reject(err);
			});
		});
	}

	get settled() {
		return this._settled;
	}

	kill() {
		this._abortController.abort();
	}
}

export class InitError extends Error {
	constructor(
		readonly initer: IniterInterface,
		message: string,
		options?: ErrorOptions
	) {
		super(message, options);
	}
}

export interface IniterInterface {
	readonly filePath: string;
	readonly promise: Promise<RunnerInterface>;

	kill(): void;
}

export interface RunnerInterface {
	readonly initer: IniterInterface;

	run(options?: RunOptions): Run;
}

export interface EntryInterface {
	(filePath: string, options?: IniterOptions): IniterInterface;
}

// // Defining constructors for interfaces hack:
// // https://stackoverflow.com/a/13700960/19662543
// //
// // It isn't perfect (e.g. ConstructorParameters<Type> complains), but if it's
// // good enough for the standard library, it's good enough for me.
// export interface RunnerInterface {
// 	readonly filePath: string;
// 	// While not all Runners need initialization, I believe the .then() syntax
// 	// offers enough convenience to outweigh the potential minor performance loss.
// 	readonly promise: Promise<RunnerInterface>;
//
// 	kill(): void;
// 	get settled(): boolean;
// 	// The reason why .run is possibly undefined (as opposed to simply throwing if
// 	// initialization fails) is because the error would be thrown within .promise
// 	// and, if caught, can preserve the Runner, erroneously allowing .run() to be
// 	// called. Leaving .run undefined is an inescapable reminder to address the
// 	// error.
// 	get run(): ((options?: RunOptions) => Run) | undefined;
// 	// TODO: Write .toString()s for each implementation. Will be helpful for error
// 	// messages and debugging.
// 	// toString(): string;
// }
// export declare const RunnerInterface: RunnerInterface & {
// 	new (filePath: string, options?: RunnerOptions): RunnerInterface;
// };
