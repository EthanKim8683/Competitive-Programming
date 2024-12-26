import {
	SamplesTestSet,
	TestSetResult,
	TestCaseVerdict,
	TestCaseResult,
} from "../types";
import makeRunners from "../utils/makeRunners";
import { PassThrough, Readable } from "stream";
import randomUnsigned from "../../utils/randomUnsigned";
import runMany from "../utils/runMany";
import WritableString from "../../utils/WritableString";

async function usingChecker(
	solutionPath: string,
	checkerPath: string
): Promise<TestSetResult> {
	const makeRunnersResult = await makeRunners([checkerPath, solutionPath]);
	if (!makeRunnersResult.success) {
		return {
			success: false,
			makeRunnerResults: makeRunnersResult.results,
		};
	}

	const [checker, solution] = makeRunnersResult.results.map(
		(result) => result.run
	);

	async function runTestCase(key: number): Promise<TestCaseResult> {
		const input = new PassThrough();
		const checkerInput = new PassThrough();
		const checkerOutput = new WritableString();

		checkerInput.write(`${key}\n`);
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
	for (let i = 0; i < n; i++) {
		promises.push(runTestCase(randomUnsigned()));
	}
	for (const key of keys) {
		promises.push(runTestCase(key));
	}
	const testCaseResults = await Promise.all(promises);

	return {
		success: true,
		makeRunnerResults: makeRunnersResult.results,
		testCaseResults,
	};
}

async function usingSamples() {}

export default (
	solutionPath: string,
	{ config: { checker: checkerPath } }: SamplesTestSet
): Promise<TestSetResult> => {
	if (checkerPath) return usingChecker(solutionPath, checkerPath);
	else return usingSamples(solutionPath);
};
