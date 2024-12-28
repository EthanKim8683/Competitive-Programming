import {
	SamplesTestSet,
	TestSetResult,
	TestCaseVerdict,
	TestCaseResult,
} from "../types";
import { PassThrough, Readable } from "stream";
import fs from "fs";
import WritableString from "../../stream/WritableString";
import randomUnsigned from "../utils/randomUnsigned";
import makeRunners from "../utils/makeRunners";
import runMany from "../utils/runMany";

const readDir = (dir: string) =>
	fs.promises.readdir(dir).then((filePaths) =>
		Promise.all(
			filePaths.map((filePath, key) =>
				fs.promises
					.readFile(filePath)
					.then((string) => [key, { success: true, string }])
					.catch((error) => [key, { success: false, error }])
			)
		)
			.then((entries) => ({
				success: true,
				results: Object.fromEntries(entries),
			}))
			.catch((error) => ({
				success: false,
				error,
			}))
	);

async function usingChecker(
	solutionPath: string,
	checkerPath: string
): Promise<TestSetResult> {
	const { success, results: makeRunnerResults } = await makeRunners([
		checkerPath,
		solutionPath,
	]);
	if (!success)
		return {
			success: false,
			makeRunnerResults,
		};
	const [checker, solution] = makeRunnerResults.map((result) => result.run);

	async function runTestCase(key: number): Promise<TestCaseResult> {
		const checkerInput = new PassThrough();
		const checkerOutput = new WritableString();

		const runManyResult = await runMany([
			checker({ stdin: checkerInput, stderr: checkerOutput }),
			solution({ stdin: Readable.from(), stdout: checkerInput }),
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
