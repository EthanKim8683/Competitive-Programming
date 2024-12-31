import { PassThrough } from "stream";
import SamplesTestSet from "../types/SamplesTestSet";
import initTogether from "../tester/helpers/initTogether";
import runTogether from "../tester/helpers/runTogether";
import testTogether from "../tester/helpers/testTogether";
import WritableString from "../../stream/WritableString";
import newRunner from "../tester/utils/newRunner";
import readFiles from "../tester/utils/readFiles";
import newRunnerErrorHandler from "../tester/utils/newRunnerErrorHandler";
import readFilesErrorHandler from "../tester/utils/readFilesErrorHandler";
import TestCaseResult from "../types/TestCaseResult";
import TestSetResult from "../types/TestSetResult";

export default async (
	solutionPath: string,
	{ config: { checker: checkerPath } }: SamplesTestSet
): Promise<TestSetResult> => {
	if (checkerPath) {
		const initResult = await initTogether([
			{
				promise: readFiles("inputs"),
				initErrorSymbol: "IE(I)",
				errorHandlers: [
					readFilesErrorHandler({
						dirExistenceErrorSymbol: "DDNE(I)",
						dirAccessErrorSymbol: "DAE(I)",
						fileExistenceErrorSymbol: "FDNE(I)",
						fileAccessErrorSymbol: "FAE(I)",
					}),
				],
			},
			{
				promise: newRunner(checkerPath),
				initErrorSymbol: "IE(C)",
				errorHandlers: [
					newRunnerErrorHandler({
						accessErrorSymbol: "DNE(C)",
						compilationErrorSymbol: "CE(C)",
					}),
				],
			},
			{
				promise: newRunner(solutionPath),
				initErrorSymbol: "IE",
				errorHandlers: [
					newRunnerErrorHandler({
						accessErrorSymbol: "DNE",
						compilationErrorSymbol: "CE",
					}),
				],
			},
		]);

		if (!initResult.success) return initResult;
		const [inputs, checker, solution] = initResult.results;

		return testTogether(
			Object.keys(inputs),
			async (key: number): Promise<TestCaseResult> => {
				const input = new PassThrough();
				const output = new PassThrough();
				const checkerInput = new PassThrough();
				const checkerStderr = new WritableString();
				checkerInput.write(`${key}`);
				output.pipe(checkerInput);

				let result = await runTogether([
					{
						promise: checker.run({
							stdin: checkerInput,
							stdout: input,
							stderr: checkerStderr,
						}),
						runtimeErrorVerdictSymbol: "RE(I)",
					},
					{
						promise: solution.run({
							stdin: input,
							stderr: output,
						}),
						runtimeErrorVerdictSymbol: "RE",
					},
				]);

				if (!result && checkerStderr.string) {
					result = {
						passed: false,
						verdictSymbol: "WA",
						reason: checkerStderr.string,
					};
				}

				if (!result) {
					result = {
						passed: true,
						verdictSymbol: "OK",
					};
				}

				return result;
			}
		);
	} else {
	}
};
