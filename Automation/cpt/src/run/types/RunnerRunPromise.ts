import { ChildProcess } from "child_process";
import Runner from "../Runner";
import RunnerRuntimeError from "./RunnerRuntimeError";

export default class RunnerRunPromise extends Promise<void> {
	readonly child: ChildProcess;

	// This constructor should only be called by `Runner`.
	constructor(
		readonly runner: Runner,
		readonly options?: Parameters<Runner["run"]>[0]
	) {
		const child = runner.spawn(options);
		super((resolve, reject) => {
			child.on("exit", (code, signal) => {
				if (code || signal) reject(new RunnerRuntimeError(this, code, signal));
				resolve();
			});

			child.on("error", (err) => {
				this.kill();
				reject(err);
			});
		});

		this.child = child;
	}

	kill() {
		// PIDs can be reassigned once a process ends. To avoid the possibility of
		// killing an unrelated process, check first if the process is still alive.
		if (this.child.exitCode === null && this.child.signalCode === null)
			this.child.kill();
	}
}
