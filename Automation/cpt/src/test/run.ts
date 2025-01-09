import program from "../run/program";
import readDir from "../run/readDir";
import { Result } from "../utils/errors";
import { KillablePromise } from "../utils/KillablePromise";
import { ResultWithVerdict } from "./types";

type IniterWithVerdict<T> = T extends (
	...args: infer A
) => KillablePromise<Result<infer S>>
	? (...args: A) => KillablePromise<ResultWithVerdict<S>>
	: never;

export const programWithVerdict: IniterWithVerdict<typeof program> = (
	...args
) => {
	const initer = program(...args);
	return new KillablePromise(
		initer.promise.then((result) => ({
			verdict: result.success
				? initer.compilerWarning === undefined
					? "OK"
					: "CW"
				: "CE",
			...result,
		})),
		initer.kill
	);
};

export const readDirWithVerdict: IniterWithVerdict<typeof readDir> = (
	...args
) => {
	const initer = readDir(...args);
	return new KillablePromise(
		initer.promise.then((result) => ({
			verdict: result.success ? "OK" : "DE",
			...result,
		})),
		initer.kill
	);
};
