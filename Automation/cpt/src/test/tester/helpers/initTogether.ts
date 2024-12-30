import RunnerInitError from "../../../run/types/RunnerInitError";
import TesterInitTask from "../types/TesterInitTask";

// Promise-typed for convenience; tasks can be destructured in the order they
// were provided. Maybe I'll make this a discriminated union to fully hide the
// TesterInitError class in the future.
export default async <T extends TesterInitTask<any>[]>(
	tasks: T
): Promise<
	| { success: false; errorSymbols: string[]; reasons: any[] }
	| { success: true; results: any[] }
> => {
	const outcomes = await Promise.allSettled(tasks.map((task) => task.promise));

	const values: any[] = [],
		errorSymbols: string[] = [],
		errors: Error[] = [],
		unhandledErrors: Error[] = [];
	for (let i = 0; i < outcomes.length; i++) {
		const outcome = outcomes[i];

		if (outcome.status === "fulfilled") values.push(outcome.value);
		else {
			const task = tasks[i];
			const { reason } = outcome;

			if (reason instanceof RunnerInitError) {
				const errorSymbol =
					{
						[RunnerInitError.Code.ACCESS_ERROR]: task.runnerAccessErrorSymbol,
						[RunnerInitError.Code.LANGUAGE_INFERENCE_ERROR]:
							task.runnerLanguageInferenceErrorSymbol,
						[RunnerInitError.Code.LANGUAGE_SUPPORT_ERROR]:
							task.runnerLanguageSupportErrorSymbol,
						[RunnerInitError.Code.LANGUAGE_ENTRY_ERROR]:
							task.runnerLanguageEntryErrorSymbol,
						[RunnerInitError.Code.COMPILATION_ERROR]:
							task.runnerCompilationErrorSymbol,
					}[reason.code] ?? task.initErrorSymbol;

				errorSymbols.push(errorSymbol);
				errors.push(reason);
				continue;
			}

			unhandledErrors.push(reason);
		}
	}

	if (unhandledErrors.length > 0)
		throw new Error("Unhandled error(s)", { cause: unhandledErrors });

	if (errors.length > 0)
		return { success: false, errorSymbols, reasons: errors };

	return { success: true, results: values };
};
