import makeRunner from "../../run/makeRunner";
import { MakeRunnerResult } from "../../run/types";

export default async (
	filePaths: string[]
): Promise<
	| {
			success: false;
			results: MakeRunnerResult[];
	  }
	| {
			success: true;
			results: Exclude<MakeRunnerResult, { success: false }>[];
	  }
> => {
	const results = await Promise.all(
		filePaths.map((filePath) => makeRunner(filePath))
	);

	if (results.every((result) => result.success))
		return { success: true, results };
	else return { success: false, results };
};
