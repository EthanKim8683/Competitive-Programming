import { PassThrough } from "stream";
import WritableString from "../../stream/WritableString";
import SamplesTestSet from "../types/SamplesTestSet";
import initTogether from "../tester/helpers/initTogether";
import runTogether from "../tester/helpers/runTogether";
import testTogether from "../tester/helpers/testTogether";
import newRunner from "../tester/utils/newRunner";
import runRunner from "../tester/utils/runRunner";
import readDir from "../tester/utils/readDir";
import readFile from "../tester/utils/readFile";
import TesterTaskResult from "../tester/types/TesterTaskResult";
import TestCaseResult from "../types/TestCaseResult";
import TestSetResult from "../types/TestSetResult";
import diffChecker from "../tester/utils/diffChecker";

export default async (
	solutionPath: string,
	{ config: { checker: checkerPath } }: SamplesTestSet
): Promise<TestSetResult> => {
	if (checkerPath) {
		const initResult = await initTogether([
			readDir("inputs", {
				default: "?E(I)",
				accessError: "DNE(I)",
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
				const checkerOutput = new WritableString();
				const input = new PassThrough();

				input.pipe(checkerInput, { end: false });

				const runResult = await runTogether([
					readFile([inputs[key], input], {
						default: "?E(I)",
						accessError: "DNE(I)",
					}),
					runRunner(
						checker.run({ stdin: checkerInput, stderr: checkerOutput }),
						{ default: "?E(C)", runtimeError: "RE(C)" }
					),
					runRunner(solution.run({ stdin: input, stdout: checkerInput }), {
						default: "?E",
						runtimeError: "RE",
					}),
				]);

				if (!runResult.success)
					return { passed: false, reasons: runResult.reasons };

				if (checkerOutput.string)
					return { passed: false, reasons: { WA: checkerOutput.string } };

				return { passed: true };
			}
		);
	} else {
		const initResult = await initTogether([
			initTogether([
				readDir("inputs", {
					default: "?E(I)",
					accessError: "DNE(I)",
				}),
				readDir("outputs", {
					default: "?E(O)",
					accessError: "DNE(O)",
				}),
			]).then(
				(
					initResult
				): TesterTaskResult<
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
						reasons: { "KE(I/O)": "Input and output cases' keys do not match" },
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
				const expectedOutput = new WritableString();
				const input = new PassThrough();
				const output = new WritableString();

				const runResult = await runTogether([
					readFile([inputs[key], input], {
						default: "?E(I)",
						accessError: "DNE(I)",
					}),
					readFile([outputs[key], expectedOutput], {
						default: "?E(O)",
						accessError: "DNE(O)",
					}),
					runRunner(
						solution.run({
							stdin: input,
							stdout: output,
						}),
						{ default: "?E", runtimeError: "RE" }
					),
				]);

				if (!runResult.success)
					return { passed: false, reasons: runResult.reasons };

				const diffCheckerOutput = diffChecker(
					output.string,
					expectedOutput.string
				);
				if (diffCheckerOutput)
					return { passed: false, reasons: { WA: diffCheckerOutput } };

				return { passed: true };
			}
		);
	}
};
