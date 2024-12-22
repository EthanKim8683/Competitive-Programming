import makeRunner from "../run/makeRunner";
import { makeExecutor } from "../run/execute";

export default async (
	filePaths: Record<string, ReturnType<typeof makeRunner>>
): Promise<
	| {
			success: true;
			runners: Record<string, ReturnType<typeof makeExecutor>>;
	  }
	| { success: false; errors: string[] }
> => {
	const keys = Object.keys(filePaths);
	const results = await Promise.all(Object.values(filePaths));

	const successes = [],
		fails = [];
	for (const result of results) {
		if (result.success) successes.push(result);
		else fails.push(result);
	}

	if (fails.length > 0)
		return {
			success: false,
			errors: fails.map((fail) => fail.error),
		};
	else
		return {
			success: true,
			runners: Object.fromEntries(
				successes.map((success, index) => [keys[index], success.run])
			),
		};
};
