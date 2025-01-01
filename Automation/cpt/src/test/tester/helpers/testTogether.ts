import TestSetResult from "../../types/TestSetResult";
import TestCaseResult from "../../types/TestCaseResult";

export default async (
	keys: number[],
	test: (key: number) => Promise<TestCaseResult>
): Promise<TestSetResult> =>
	Promise.all(keys.map((key) => test(key))).then((results) => ({
		success: true,
		results: Object.fromEntries(
			results.map((testCaseResult, index) => [keys[index], testCaseResult])
		),
	}));
