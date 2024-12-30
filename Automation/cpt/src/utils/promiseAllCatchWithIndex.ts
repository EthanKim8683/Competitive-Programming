export type IndexedError<T extends Error> = T & { index: number };
export default <T>(
	promises: Iterable<T | PromiseLike<T>>
): Promise<Awaited<T>[]> =>
	Promise.all(
		[...promises].map((promise, index) =>
			(async () => promise)().catch(<S extends Error>(err: S) => {
				(err as IndexedError<S>).index = index;
				throw err;
			})
		)
	);
