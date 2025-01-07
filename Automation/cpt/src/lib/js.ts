import crypto from "crypto";

export type PromiseSettledResults<T extends readonly any[]> = {
	[K in keyof T]: PromiseSettledResult<T[K]>;
};

// It is recommended to pass this function into a .then() following a
// Promise.allSettled() to be caught afterwards.
export function allFulfilled<T extends readonly any[]>(
	results: PromiseSettledResults<T>
): T {
	if (results.some((result) => result.status !== "fulfilled")) throw results;
	return results as T;
}

export type NotAllFulfilledCallback = <T extends readonly any[]>(
	results: PromiseSettledResults<T>
) => any;

// https://stackoverflow.com/a/28061457/19662543
export const randomUnsigned = () => crypto.randomBytes(4).readUInt32BE();

// https://stackoverflow.com/a/43044960/19662543
export const randomUnsigneds = (n: number) =>
	Array.from({ length: n }, () => randomUnsigned());
