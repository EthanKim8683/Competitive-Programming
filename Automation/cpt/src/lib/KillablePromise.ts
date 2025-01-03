import { isPromise } from "util/types";

export interface KillablePromise<T> {
	readonly promise: Promise<T>;
	readonly kill: () => void;
}

type Resolvable<T> = T | Promise<T> | KillablePromise<T>;

type AwaitedKillablePromise<T> = T extends KillablePromise<infer S> ? S : never;

type AwaitedKillablePromises<T> = {
	[K in keyof T]: AwaitedKillablePromise<T[K]>;
};

type SettledKillablePromise<T> =
	T extends KillablePromise<infer S>
		? { status: "fulfilled"; value: S } | { status: "rejected"; reason: any }
		: never;

type SettledKillablePromises<T> = {
	[K in keyof T]: SettledKillablePromise<T[K]>;
};

export class KillablePromise<T> implements KillablePromise<T> {
	constructor(
		readonly promise: Promise<T>,
		readonly kill: () => void = () => {}
	) {}

	static all<T extends Resolvable<any>[]>(
		values: T
	): KillablePromise<AwaitedKillablePromises<T>> {
		const kill = (): void => values.forEach((value) => value.kill?.());

		const promise = Promise.all(
			values.map((value) =>
				KillablePromise.resolve(value).promise.catch((err) => {
					kill();
					throw err;
				})
			)
		);

		return new KillablePromise(
			promise as Promise<AwaitedKillablePromises<T>>,
			kill
		);
	}

	static allSettled<T extends Resolvable<any>[]>(
		values: T
	): KillablePromise<SettledKillablePromises<T>> {
		const kill = (): void => values.forEach((value) => value?.kill());

		const promise = Promise.all(
			values.map((value: Resolvable<any>) =>
				KillablePromise.resolve(value).promise.then(
					(value) => ({ status: "fulfilled" as const, value }),
					(reason) => ({ status: "rejected" as const, reason })
				)
			)
		);

		return new KillablePromise(
			promise as Promise<SettledKillablePromises<T>>,
			kill
		);
	}

	static reject<T>(reason: T): KillablePromise<T> {
		return new KillablePromise(Promise.reject<T>(reason));
	}

	static resolve<T>(value: Resolvable<T>): KillablePromise<T> {
		if (isKillablePromise(value)) return value;
		else return new KillablePromise(Promise.resolve<T>(value));
	}
}

export const isKillablePromise = (
	value: unknown
): value is KillablePromise<unknown> =>
	typeof value === "object" &&
	value !== null &&
	"promise" in value &&
	isPromise(value.promise) &&
	"kill" in value &&
	typeof value.kill === "function";
