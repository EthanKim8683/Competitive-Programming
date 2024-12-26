import {
	GeneratorTestSet,
	TestSetResult,
	TestCaseVerdict,
	TestCaseResult,
} from "../types";
import { PassThrough, Readable } from "stream";
import WritableString from "../../stream/WritableString";
import randomUnsigned from "../utils/randomUnsigned";
import makeRunners from "../utils/makeRunners";
import runMany from "../utils/runMany";

export default async (
	solutionPath: string,
	{
		config: { generator: generatorPath, checker: checkerPath, n, keys },
	}: GeneratorTestSet
): Promise<TestSetResult> => {
	const { success, results: makeRunnerResults } = await makeRunners([
		generatorPath,
		checkerPath,
		solutionPath,
	]);
	if (!success) return { success, makeRunnerResults };
	const [generator, checker, solution] = makeRunnerResults.map(
		(result) => result.run
	);

	async function runTestCase(key: number): Promise<TestCaseResult> {
		const input = new PassThrough();
		const checkerInput = new PassThrough();
		const checkerOutput = new WritableString();
		input.pipe(checkerInput);

		const runManyResult = await runMany([
			generator({ stdin: Readable.from(`${key}\n`), stdout: input }),
			checker({ stdin: checkerInput, stderr: checkerOutput }),
			solution({ stdin: input, stdout: checkerInput }),
		]);

		if (!runManyResult.success)
			return {
				key,
				verdict: [
					TestCaseVerdict.GENERATOR_RUNTIME_ERROR,
					TestCaseVerdict.CHECKER_RUNTIME_ERROR,
					TestCaseVerdict.RUNTIME_ERROR,
				][runManyResult.index],
			};

		if (checkerOutput.string)
			return {
				key,
				verdict: TestCaseVerdict.WRONG_ANSWER,
				hint: checkerOutput.string,
			};

		return { key, verdict: TestCaseVerdict.OK };
	}

	const promises = [];
	for (let i = 0; i < n; i++) promises.push(runTestCase(randomUnsigned()));
	for (const key of keys) promises.push(runTestCase(key));
	const testCaseResults = await Promise.all(promises);

	return { success, makeRunnerResults, testCaseResults };
};
