import { PassThrough, Readable } from "stream";
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
import recordIntersection from "../../utils/recordIntersection";

export default async (
	solutionPath: string,
	{ config: { checker: checkerPath } }: SamplesTestSet
): Promise<TestSetResult> => {
	if (checkerPath) {
		const initResult = await initTogether([
			{
				promise: readFiles("inputs"),
				initErrorSymbol: "IE(I/i)",
				errorHandlers: [
					readFilesErrorHandler({
						dirExistenceErrorSymbol: "DNE(I)",
						dirAccessErrorSymbol: "AE(I)",
						fileAccessErrorSymbol: "AE(i)",
						fileNameErrorSymbol: "NE(i)",
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
			Object.keys(inputs).map((key) => parseInt(key)),
			async (key: number): Promise<TestCaseResult> => {
				const checkerInput = new PassThrough();
				const checkerStderr = new WritableString();

				let result = await runTogether([
					{
						promise: checker.run({
							stdin: checkerInput,
							stderr: checkerStderr,
						}),
						runtimeErrorVerdictSymbol: "RE(I)",
					},
					{
						promise: solution.run({
							stdin: Readable.from(inputs[key]),
							stderr: checkerInput,
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
		const initResult = await initTogether([
			{
				promise: readFiles("inputs"),
				initErrorSymbol: "IE(I/i)",
				errorHandlers: [
					readFilesErrorHandler({
						dirExistenceErrorSymbol: "DNE(I)",
						dirAccessErrorSymbol: "AE(I)",
						fileAccessErrorSymbol: "AE(i)",
						fileNameErrorSymbol: "NE(i)",
					}),
				],
			},
			{
				promise: readFiles("outputs"),
				initErrorSymbol: "IE(O/o)",
				errorHandlers: [
					readFilesErrorHandler({
						dirExistenceErrorSymbol: "DNE(O)",
						dirAccessErrorSymbol: "AE(o)",
						fileAccessErrorSymbol: "AE(o)",
						fileNameErrorSymbol: "NE(o)",
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
		const [inputs, outputs, solution] = initResult.results;

		return testTogether(
			// TODO: Throw error when `inputs`/`outputs` are missing keys from each
			// other.
			Object.keys(recordIntersection(inputs, outputs)).map((key) =>
				parseInt(key)
			),
			async (key: number): Promise<TestCaseResult> => {
				const output = new WritableString();

				let result = await runTogether([
					{
						promise: solution.run({
							stdin: Readable.from(inputs[key]),
							stderr: output,
						}),
						runtimeErrorVerdictSymbol: "RE",
					},
				]);

				if (
					!result &&
					JSON.stringify(outputs[key].split(/\w/g)) !=
						JSON.stringify(output.string.split(/\w/g))
				) {
					result = {
						passed: false,
						verdictSymbol: "WA",
						// TODO: `reason`
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
	}
};
