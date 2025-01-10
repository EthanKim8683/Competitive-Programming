import _program, { Process } from "../run/program";
import _readFiles from "../run/readFiles";
import { Result } from "../utils/errors";
import { KillablePromise } from "../utils/KillablePromise";
import { Verdict } from "./types";

type Initer<T> = KillablePromise<{ result?: T; verdict: Verdict }>;

export const program = (
	...args: Parameters<typeof _program>
): ReturnType<typeof _program> extends KillablePromise<Result<infer T>>
	? Initer<T>
	: never => {
	const base = _program(...args);
	return new KillablePromise(
		base.promise.then((result) =>
			result.success
				? {
						result: result.result,
						verdict: {
							symbol: base.compilerWarning ? "CW" : "OK",
							reason: base.compilerWarning,
						},
					}
				: { verdict: { symbol: "CE", reason: result.error } }
		),
		base.kill
	);
};

export const readFiles = (
	...args: Parameters<typeof _readFiles>
): ReturnType<typeof _readFiles> extends KillablePromise<Result<infer T>>
	? Initer<T>
	: never => {
	const base = _readFiles(...args);
	return new KillablePromise(
		base.promise.then((result) =>
			result.success
				? { result: result.result, verdict: { symbol: "OK" } }
				: { verdict: { symbol: "CE", reason: result.error } }
		),
		base.kill
	);
};

type Results<T> =
	| {
			[K in keyof T]: T[K] extends [string, Initer<infer S>] ? S : never;
	  }
	| undefined;

type Verdicts<T> = {
	[K in keyof T]: T[K] extends [infer S, Initer<any>] ? [S, Verdict] : never;
};

export async function initTogether<T extends readonly [string, Initer<any>][]>(
	initers: T
): Promise<{
	results: Results<T>;
	verdicts: Verdicts<T>;
}> {
	const initerResults = await KillablePromise.all(
		initers.map((initer) => initer[1].promise)
	).promise;

	// TypeScript "forgets" constant types when mapping/filtering; typing as any
	// at least hides the resulting warnings
	let results: any = initerResults
		.map((initerResult) => initerResult.result)
		.filter((result) => result !== undefined);
	if (results.length < initers.length) results = undefined;

	const verdicts: any = initerResults.map((initerResult, index) => [
		initers[index][0],
		initerResult.verdict,
	]);

	return { results, verdicts };
}

class VerdictError extends Error {
	constructor(readonly verdict: Verdict) {
		super();
	}
}

export const runTogether = <T extends [string, Process][]>(
	processes: T
): Promise<Verdict | undefined> =>
	KillablePromise.all(
		processes.map((process) =>
			process[1].promise.then((exitStatus) => {
				if (exitStatus.exitCode !== 0 || exitStatus.signalCode !== null)
					throw new VerdictError({ symbol: "RE", reason: exitStatus });
			})
		)
	)
		.promise.then(() => undefined)
		.catch((err) => {
			if (!(err instanceof VerdictError)) throw err;
			return err.verdict;
		});

export const testTogether = async <T extends number | string>(
	keys: T[],
	runTestCase: (key: T) => Promise<Verdict>
): Promise<[T, Verdict][]> =>
	Promise.all(
		keys.map((key) =>
			runTestCase(key).then(
				(testCaseResult) => [key, testCaseResult] as [T, Verdict]
			)
		)
	);
