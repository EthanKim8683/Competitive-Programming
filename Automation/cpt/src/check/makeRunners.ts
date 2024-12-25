import makeRunner from "../run/makeRunner";
import { makeExecutor } from "../run/execute";

export default async (
	filePaths: ReturnType<typeof makeRunner>[]
): Promise<
	| {
			success: true;
			runners: ReturnType<typeof makeExecutor>[];
	  }
	| { success: false; errors: string[] }
> => {
	const results = await Promise.all(filePaths);

	const successful = [],
		unsuccessful = [];
	for (const result of results) {
		if (result.success) successful.push(result);
		else unsuccessful.push(result);
	}

	if (unsuccessful.length > 0)
		return {
			success: false,
			errors: unsuccessful.map((fail) => fail.error),
		};
	else
		return {
			success: true,
			runners: successful.map((success) => success.run),
		};
};
