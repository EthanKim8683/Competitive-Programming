import { ChildProcess } from "child_process";
import Runner from "../Runner";
import RunnerRuntimeError from "./RunnerRuntimeError";

// I override `Promise` for the `await` syntax.
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

	// Instance methods (`.then()`, `.catch()`, `.finally()`) return `Promise`s,
	// since what is executed once the process ends isn't necessarily killable.
	static get [Symbol.species]() {
		return Promise;
	}

	// Override `Promise`'s static methods to be effectively unusable.
	static all(..._: never): never {
		throw "Use `Promise.all` instead";
	}
	static allSettled(..._: never): never {
		throw "Use `Promise.allSettled` instead";
	}
	static any(..._: never): never {
		throw "Use `Promise.any` instead";
	}
	static race(..._: never): never {
		throw "Use `Promise.race` instead";
	}
	static reject(..._: never): never {
		throw "Use `Promise.reject` instead";
	}
	static resolve(..._: never): never {
		throw "Use `Promise.resolve` instead";
	}
	static try(..._: never): never {
		throw "Use `Promise.try` instead";
	}
	static withResolvers(..._: never): never {
		throw "Use `Promise.withResolvers` instead";
	}
}
