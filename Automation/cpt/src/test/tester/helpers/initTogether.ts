import TesterTaskResult from "../types/TesterTaskResult";
import TesterInitTask from "../types/TesterInitTask";
import coerceArray from "../../../utils/coerceArray";

// Assumes tasks are independent. Analogous to `Promise.allSettled`.
export default async <T extends any[]>(tasks: {
	[K in keyof T]: ReturnType<TesterInitTask<T[K]>>;
}): Promise<TesterTaskResult<T>> => {
	const initResults = await Promise.all(tasks);

	// TODO: Get rid of the `any`s (if possible).
	const result: any[] = [],
		reasons: Record<string, Error | string | (Error | string)[]> = {};
	for (const initResult of initResults)
		if (initResult.success) result.push(initResult.result);
		else
			for (const key in initResult.reasons)
				if (key in reasons) {
					reasons[key] = [
						...coerceArray(reasons[key]),
						...coerceArray(initResult.reasons[key]),
					];
				} else reasons[key] = initResult.reasons[key];

	if (Object.keys(reasons).length > 0)
		return {
			success: false,
			reasons,
		};
	else
		return {
			success: true,
			result: result as T,
		};
};
