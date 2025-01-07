type Resolvable<T> = T | Promise<T> | KillablePromise<T>;

export type KillablePromises<T extends readonly any[]> = {
	[K in keyof T]: KillablePromise<T[K]>;
};

export type AwaitedKillablePromise<T> =
	T extends KillablePromise<infer S> ? S : T extends Promise<infer U> ? U : T;
export type AwaitedKillablePromises<T extends readonly any[]> = {
	[K in keyof T]: AwaitedKillablePromise<T[K]>;
};

export type SettledKillablePromise<T> = PromiseSettledResult<
	AwaitedKillablePromise<T>
>;
export type SettledKillablePromises<T extends readonly any[]> = {
	[K in keyof T]: SettledKillablePromise<T[K]>;
};

// Promises that you can kill. For processes and more.
export class KillablePromise<T> {
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
		private _promise: Promise<T>,
		readonly kill: () => void = () => {}
	) {
		// If .catch() is chained after the promise rejects, it doesn't catch the
		// error. This can result in .promise throwing before it can be handled
		// post-construction.
		//
		// To fix this, we catch, but not replace .promise, effectively putting it
		// in a dormant state, and resolve entirely new instances, active states,
		// when getting .promise.
		const dormant = _promise.catch(() => {});

		KillablePromise._livingPromises.add(this);
		dormant.finally(() => KillablePromise._livingPromises.delete(this));
	}

	get promise() {
		return Promise.resolve(this._promise);
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
