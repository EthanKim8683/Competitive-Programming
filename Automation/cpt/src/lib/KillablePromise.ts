import z from "zod";
import { promiseSchema } from "./node";

export interface KillablePromise<T> {
	readonly promise: Promise<T>;

	kill(): void;
}

export const killablePromiseSchema = z.object({
	promise: promiseSchema,
	kill: z.function().args().returns(z.void()),
});

export function isKillablePromise(
	value: any | KillablePromise<any>
): value is KillablePromise<any> {
	return killablePromiseSchema.safeParse(value).success;
}

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
export const KillablePromise = {
	all<T extends (any | KillablePromise<any>)[]>(
		values: T
	): KillablePromise<AwaitedKillablePromises<T>> {
		const kill = (): void => values.forEach((value) => value.kill?.());

		const promise = Promise.all(
			values.map((value) => {
				KillablePromise.resolve(value).promise.catch((err) => {
					kill();
					throw err;
				});
			})
		);

		return { promise: promise as Promise<AwaitedKillablePromises<T>>, kill };
	},

	allSettled<T extends (any | KillablePromise<any>)[]>(
		values: T
	): KillablePromise<SettledKillablePromises<T>> {
		const kill = (): void => values.forEach((value) => value?.kill());

		const promise = Promise.all(
			values.map((value: any | KillablePromise<any>) =>
				KillablePromise.resolve(value).promise.then(
					(value) => ({ status: "fulfilled" as const, value }),
					(reason) => ({ status: "rejected" as const, reason })
				)
			)
		);

		return { promise: promise as Promise<SettledKillablePromises<T>>, kill };
	},

	reject<T>(reason: T): KillablePromise<T> {
		return { promise: Promise.reject<T>(reason), kill: (): void => {} };
	},

	resolve<T>(value: T | KillablePromise<T>): KillablePromise<T> {
		if (isKillablePromise(value)) return value;
		else return { promise: Promise.resolve<T>(value), kill: (): void => {} };
	},

	// TODO: any, race, try, withResolvers
};
