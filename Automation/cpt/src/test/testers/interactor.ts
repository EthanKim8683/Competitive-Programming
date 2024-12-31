import { PassThrough } from "stream";
import InteractorTestSet from "../types/InteractorTestSet";
import initTogether from "../tester/helpers/initTogether";
import runTogether from "../tester/helpers/runTogether";
import testTogether from "../tester/helpers/testTogether";
import WritableString from "../../stream/WritableString";
import newRunner from "../tester/utils/newRunner";
import newRunnerErrorHandler from "../tester/utils/newRunnerErrorHandler";
import randomUnsigneds from "../tester/utils/randomUnsigneds";
import TestCaseResult from "../types/TestCaseResult";
import TestSetResult from "../types/TestSetResult";

export default async (
	solutionPath: string,
	{ config: { interactor: interactorPath, n, keys } }: InteractorTestSet
): Promise<TestSetResult> => {
	const initResult = await initTogether([
		{
			promise: newRunner(interactorPath),
			initErrorSymbol: "IE(I)",
			errorHandlers: [
				newRunnerErrorHandler({
					accessErrorSymbol: "DNE(I)",
					compilationErrorSymbol: "CE(I)",
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
	const [interactor, solution] = initResult.results;

	return testTogether(
		[...keys, ...randomUnsigneds(n)],
		async (key: number): Promise<TestCaseResult> => {
			const interactorInput = new PassThrough();
			const interactorStderr = new WritableString();
			const input = new PassThrough();
			const output = new PassThrough();
			interactorInput.write(`${key}\n`);
			output.pipe(interactorInput);

			let result = await runTogether([
				{
					promise: interactor.run({
						stdin: interactorInput,
						stdout: input,
						stderr: interactorStderr,
					}),
					runtimeErrorVerdictSymbol: "RE(I)",
				},
				{
					promise: solution.run({
						stdin: input,
						stdout: output,
					}),
					runtimeErrorVerdictSymbol: "RE",
				},
			]);

			if (!result && interactorStderr.string) {
				result = {
					passed: false,
					verdictSymbol: "WA",
					reason: interactorStderr.string,
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
};
