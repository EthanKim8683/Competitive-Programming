export type PromiseSettledResults<T extends readonly any[]> = {
	[K in keyof T]: PromiseSettledResult<T[K]>;
};

// It is recommended to pass this function into a .then() following a
// Promise.allSettled() to be caught afterwards
export function allFulfilled<T extends readonly any[]>(
	results: PromiseSettledResults<T>
): T {
	if (results.some((result) => result.status !== "fulfilled")) throw results;
	return results as T;
}

export type NotAllFulfilledCallback = <T extends readonly any[]>(
	results: PromiseSettledResults<T>
) => any;
