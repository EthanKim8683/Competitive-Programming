import { PassThrough, Readable } from "stream";
import SamplesTestSet from "../types/SamplesTestSet";
import initTogether from "../tester/helpers/initTogether";
import runTogether from "../tester/helpers/runTogether";
import testTogether from "../tester/helpers/testTogether";
import WritableString from "../../stream/WritableString";
import newRunner from "../tester/utils/newRunner";
import readFiles from "../tester/utils/readFiles";
import TestCaseResult from "../types/TestCaseResult";
import TestSetResult from "../types/TestSetResult";
import TesterInitResult from "../tester/types/TesterInitResult";
import diffChecker from "../tester/utils/diffChecker";

// TODO: Rewrite this entire thing. It sucks.
export default async (
	solutionPath: string,
	{ config: { checker: checkerPath } }: SamplesTestSet
): Promise<TestSetResult> => {
	if (checkerPath) {
		const initResult = await initTogether([
			readFiles("inputs", {
				default: "IE(I/i)",
				dirAccessError: "DNE(I)",
				fileAccessError: "DNE(i)",
				fileNameError: "NE(i)",
			}),
			newRunner([checkerPath], {
				default: "IE(C)",
				accessError: "DNE(C)",
				compilationError: "CE(C)",
			}),
			newRunner([solutionPath], {
				default: "IE",
				accessError: "DNE",
				compilationError: "CE",
			}),
		]);

		if (!initResult.success) return initResult;
		const [inputs, checker, solution] = initResult.result;

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
			initTogether([
				readFiles("inputs", {
					default: "IE(I/i)",
					dirAccessError: "DNE(I)",
					fileAccessError: "DNE(i)",
					fileNameError: "NE(i)",
				}),
				readFiles("outputs", {
					default: "IE(O/o)",
					dirAccessError: "DNE(O)",
					fileAccessError: "DNE(o)",
					fileNameError: "NE(o)",
				}),
			]).then(
				(
					initResult
				): TesterInitResult<
					[Record<number, string>, Record<number, string>]
				> => {
					if (!initResult.success) return initResult;
					const [inputs, outputs] = initResult.result;

					if (
						JSON.stringify(Object.keys(inputs)) ==
						JSON.stringify(Object.keys(outputs))
					)
						return initResult;

					return {
						success: false,
						reasons: {
							"KE(I/O)": new Error("Input and output cases' keys do not match"),
						},
					};
				}
			),
			newRunner([solutionPath], {
				default: "IE",
				accessError: "DNE",
				compilationError: "CE",
			}),
		]);

		if (!initResult.success) return initResult;
		const [[inputs, outputs], solution] = initResult.result;

		return testTogether(
			Object.keys(inputs).map((key) => parseInt(key)),
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

				if (!result) {
					const diffCheck = diffChecker(output.string, outputs[key]);
					if (diffCheck)
						result = {
							passed: false,
							verdictSymbol: "WA",
							reason: diffCheck,
						};
				}

				if (!result)
					result = {
						passed: true,
						verdictSymbol: "OK",
					};

				return result;
			}
		);
	}
};
