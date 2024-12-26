import {
	InteractorTestSet,
	TestSetResult,
	TestCaseVerdict,
	TestCaseResult,
} from "../types";
import makeRunners from "../utils/makeRunners";
import { PassThrough } from "stream";
import randomUnsigned from "../../utils/randomUnsigned";
import runMany from "../utils/runMany";
import WritableString from "../../utils/WritableString";

export default async (
	solutionPath: string,
	{ config: { interactor: interactorPath, n, keys } }: InteractorTestSet
): Promise<TestSetResult> => {
	const makeRunnersResult = await makeRunners([interactorPath, solutionPath]);
	if (!makeRunnersResult.success) {
		return {
			success: false,
			makeRunnerResults: makeRunnersResult.results,
		};
	}

	const [interactor, solution] = makeRunnersResult.results.map(
		(result) => result.run
	);

	async function runTestCase(key: number): Promise<TestCaseResult> {
		const interactorInput = new PassThrough();
		const interactorOutput = new PassThrough();
		const interactorError = new WritableString();

		interactorInput.write(`${key}\n`);

		const runManyResult = await runMany([
			interactor({ stdin: interactorInput, stdout: interactorOutput }),
			solution({ stdin: interactorOutput, stdout: interactorInput }),
		]);

		if (!runManyResult.success)
			return {
				key,
				verdict: [
					TestCaseVerdict.INTERACTOR_RUNTIME_ERROR,
					TestCaseVerdict.RUNTIME_ERROR,
				][runManyResult.index],
			};

		if (interactorError.string)
			return {
				key,
				verdict: TestCaseVerdict.WRONG_ANSWER,
				hint: interactorError.string,
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
};
