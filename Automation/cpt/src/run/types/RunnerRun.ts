import { ChildProcess } from "child_process";
import Runner from "../Runner";
import RunnerRuntimeError from "./RunnerRuntimeError";

export default class RunnerRun {
	readonly child: ChildProcess;
	readonly promise: Promise<void>;

	// This constructor should only be called by `Runner`.
	constructor(
		readonly runner: Runner,
		readonly options?: Parameters<Runner["run"]>[0]
	) {
		this.child = runner.spawn(options);
		this.promise = new Promise((resolve, reject) => {
			this.child.on("exit", (code, signal) => {
				if (code || signal) reject(new RunnerRuntimeError(this, code, signal));
				resolve();
			});

			this.child.on("error", (err) => {
				this.kill();
				reject(err);
			});
		});
	}

	kill() {
		// PIDs can be reassigned once a process ends. To avoid the possibility of
		// killing an unrelated process, check first if the process is still alive.
		if (this.child.exitCode === null && this.child.signalCode === null)
			this.child.kill();
	}

	// Instance methods (`.then()`, `.catch()`, `.finally()`) return `Promise`s,
	// since what is executed once the process ends isn't necessarily killable.
	static get [Symbol.species]() {
		return Promise;
	}
}
