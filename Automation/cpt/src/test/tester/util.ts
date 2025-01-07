import { KillablePromise } from "../../lib/KillablePromise";
import { InitError, Invoker, Process, ProcessError } from "../../run/base";
import { InitResult, TestCaseResult } from "../types";

export async function initTogether<
	T extends readonly Invoker[],
>(initerOptions: {
	[K in keyof T]: {
		initer: KillablePromise<T[K]>;
		symbol: string;
		errorVerdict?: string;
		warningVerdict?: string;
	};
}): Promise<
	{ initResults: Record<string, InitResult> } & (
		| { success: true; invokers: T }
		| { success: false }
	)
> {
	// Provided that I do my own error handling, KillablePromise.all lets
	// unhandled errors short-circuit and kill all promises immediately.
	const initerResults = await KillablePromise.all(
		// While mapping, TypeScript forgets the elements only extend Invoker and
		// mistakes them for actual Invokers. This becomes an issue when returning,
		// hence the icky "as any as T" at the end.
		initerOptions.map(
			({ initer, symbol, errorVerdict = "IE", warningVerdict = "OK" }) =>
				new KillablePromise(
					initer.promise
						.then((invoker) => ({
							initResultsEntry: [
								symbol,
								invoker.warning !== undefined
									? { verdict: warningVerdict, reason: invoker.warning }
									: { verdict: "OK" },
							] as const,
							success: true as const,
							invoker: invoker,
						}))
						.catch((err) => {
							if (!(err instanceof InitError)) throw err;

							return {
								initResultsEntry: [
									symbol,
									{ verdict: errorVerdict, reason: err },
								] as const,
								success: false as const,
							};
						}),
					initer.kill
				)
		)
	).promise;

	const initResultsEntries = [],
		invokers = [];
	let success = true;
	for (const initerResult of initerResults) {
		initResultsEntries.push(initerResult.initResultsEntry);
		if (initerResult.success) invokers.push(initerResult.invoker);
		else success = false;
	}
	const initResults = Object.fromEntries(initResultsEntries);

	return success
		? { initResults, success, invokers: invokers as any as T }
		: { initResults, success };
}

// TODO: Handle exit status runtime errors.
export const processTogether = async (
	processOptions: {
		process: Process;
		symbol: string;
		errorVerdict?: string;
	}[]
): Promise<TestCaseResult | undefined> =>
	KillablePromise.all(processOptions.map(({ process }) => process))
		.promise.then(() => undefined)
		.catch((err) => {
			if (!(err instanceof ProcessError)) throw err;

			const { symbol, errorVerdict = "RE" } = processOptions.find(
				(processOption) => processOption.process === err.process
			)!;
			return {
				verdict: `${errorVerdict}(${symbol})`,
				reason: err,
			};
		});

export const testTogether = async <T extends number | string>(
	keys: T[],
	runTestCase: (key: T) => Promise<TestCaseResult>
): Promise<Record<T, TestCaseResult>> =>
	Promise.all(
		keys.map((key) =>
			runTestCase(key).then((testCaseResult) => [key, testCaseResult] as const)
		)
	).then((entries) => Object.fromEntries(entries) as Record<T, TestCaseResult>);
