import TesterInitResult from "../types/TesterInitResult";
import TesterInitTask from "../types/TesterInitTask";
import coerceArray from "../../../utils/coerceArray";

export default async <T extends any[]>(tasks: {
	[K in keyof T]: ReturnType<TesterInitTask<T[K]>>;
}): Promise<TesterInitResult<T>> => {
	const initResults = await Promise.all(tasks);

	// TODO: Get rid of the `any`s (if possible).
	const result: any[] = [],
		reasons: Record<string, Error | Error[]> = {};
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
