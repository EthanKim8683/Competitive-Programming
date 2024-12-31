import TesterInitTask from "../types/TesterInitTask";

export default async <T extends any[]>(tasks: {
	[K in keyof T]: TesterInitTask<T[K]>;
}): Promise<
	| { success: false; errorSymbols: string[]; reasons: any[] }
	| { success: true; results: T }
> => {
	const outcomes = await Promise.allSettled(tasks.map((task) => task.promise));

	// TODO: Get rid of the `any`s (if possible).
	const values: any[] = [],
		errorSymbols: string[] = [],
		errors: Error[] = [],
		unhandledErrors: Error[] = [];
	for (let i = 0; i < outcomes.length; i++) {
		const outcome = outcomes[i];

		if (outcome.status === "fulfilled") values.push(outcome.value);
		else {
			const { errorHandlers = [], initErrorSymbol } = tasks[i];
			const { reason } = outcome;

			let errorSymbol: string | undefined;
			for (const errorHandler of errorHandlers) {
				errorSymbol ??= errorHandler(reason, initErrorSymbol);
			}

			if (errorSymbol) {
				errors.push(reason);
				errorSymbols.push(errorSymbol);
			} else unhandledErrors.push(reason);
		}
	}

	if (unhandledErrors.length > 0)
		throw new Error("Unhandled error(s)", { cause: unhandledErrors });

	if (errors.length > 0)
		return { success: false, errorSymbols, reasons: errors };

	return { success: true, results: values as T };
};
