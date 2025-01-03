export interface KillablePromise<T> {
	readonly promise: Promise<T>;

	kill(): void;
}

type KillablePromises<T extends any[]> = {
	[K in keyof T]: KillablePromise<T[K]>;
};
type PromiseSettledResults<T extends any[]> = {
	[K in keyof T]: PromiseSettledResult<T[K]>;
};
export const KillablePromise = {
	all<T extends any[]>(promises: KillablePromises<T>): KillablePromise<T> {
		const kill = (): void => promises.forEach((promise) => promise.kill());

		const promise = Promise.all(
			promises.map((promise) =>
				promise.promise.catch((err) => {
					kill();
					throw err;
				})
			)
		);

		return { promise: promise as Promise<T>, kill };
	},

	allSettled<T extends any[]>(
		promises: KillablePromises<T>
	): KillablePromise<PromiseSettledResults<T>> {
		const kill = (): void => promises.forEach((promise) => promise.kill());

		const promise = Promise.all(
			promises.map(
				<E>(promise: KillablePromise<E>) =>
					promise.promise
						.then((value) => ({ status: "fulfilled", value }))
						.catch((reason) => ({ status: "rejected", reason })) as Promise<
						PromiseSettledResult<E>
					>
			)
		);

		return { promise: promise as Promise<PromiseSettledResults<T>>, kill };
	},
};
