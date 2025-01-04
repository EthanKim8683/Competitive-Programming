import { Readable, Writable } from "stream";

import { KillablePromise } from "../lib/KillablePromise";

// Classes implementing interfaces extending other classes do not retain
// implementation details.
//
// A workaround is to define a dummy class of the same name as the interface
// and extend the dummy class while implementing the interface.
export class Initer extends KillablePromise<Invoker> {}
export interface Initer extends KillablePromise<Invoker> {}

// Custom errors help distinguish handled errors.
export class InitError extends Error {
	constructor(
		readonly initer: Initer,
		message: string,
		options?: ErrorOptions
	) {
		super(message, options);
	}
}

export interface Invoker {
	readonly initer: Initer;

	invoke(...args: any[]): any;
}

export class InvokeError extends Error {
	constructor(
		readonly invoker: Invoker,
		message: string,
		options?: ErrorOptions
	) {
		super(message, options);
	}
}

// Based on shell processes.
export class Process extends KillablePromise<void> {}
export interface Process extends KillablePromise<void> {
	readonly invoker: Invoker;
	readonly stdin: Writable;
	readonly stdout: Readable;
	readonly stderr: Readable;
}

export class ProcessError extends Error {
	constructor(
		readonly process: Process,
		message: string,
		options?: ErrorOptions
	) {
		super(message, options);
	}
}
