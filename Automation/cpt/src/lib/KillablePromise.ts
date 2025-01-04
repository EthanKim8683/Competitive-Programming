// Promises that you can kill. For processes and more.
export interface KillablePromise<T> {
	readonly promise: Promise<T>;
	readonly kill: () => void;
}

type Resolvable<T> = T | Promise<T> | KillablePromise<T>;

export type AwaitedKillablePromise<T> =
	T extends KillablePromise<infer S> ? S : never;
export type AwaitedKillablePromises<T extends readonly any[]> = {
	[K in keyof T]: AwaitedKillablePromise<T[K]>;
};

export type SettledKillablePromise<T> =
	T extends KillablePromise<infer S> ? PromiseSettledResult<S> : never;
export type SettledKillablePromises<T extends readonly any[]> = {
	[K in keyof T]: SettledKillablePromise<T[K]>;
};

export class KillablePromise<T> implements KillablePromise<T> {
	private static _livingPromises = (() => {
		const livingPromises = new Set<KillablePromise<any>>();

		let sigintedRecently = false;
		process.on("SIGINT", () => {
			// Force exit if two SIGINTs are sent in quick succession.
			if (sigintedRecently) process.exit(0);

			// Otherwise, kill all living promises.
			for (const livingPromise of livingPromises) livingPromise.kill();

			sigintedRecently = true;
			setTimeout(() => {
				sigintedRecently = false;
			}, 100);
		});

		return livingPromises;
	})();

	constructor(
		readonly promise: Promise<T>,
		readonly kill: () => void = () => {}
	) {
		KillablePromise._livingPromises.add(this);
		promise.then(() => KillablePromise._livingPromises.delete(this));
	}

	static all<T extends readonly Resolvable<any>[]>(
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

	static allSettled<T extends readonly Resolvable<any>[]>(
		values: T
	): KillablePromise<SettledKillablePromises<T>> {
		const kill = (): void => values.forEach((value) => value?.kill());

		const promise = Promise.allSettled(values.map((value) => value.promise));

		return new KillablePromise(
			promise as Promise<SettledKillablePromises<T>>,
			kill
		);
	}

	static reject<T>(reason: T): KillablePromise<T> {
		return new KillablePromise(Promise.reject<T>(reason));
	}

	static resolve<T>(value: Resolvable<T>): KillablePromise<T> {
		if (value instanceof KillablePromise) return value;
		else return new KillablePromise(Promise.resolve<T>(value));
	}
}
