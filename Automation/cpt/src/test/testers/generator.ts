import { PassThrough, Readable } from "stream";
import GeneratorTestSet from "../types/GeneratorTestSet";
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
	{
		config: { generator: generatorPath, checker: checkerPath, n, keys },
	}: GeneratorTestSet
): Promise<TestSetResult> => {
	const initResult = await initTogether([
		{
			promise: newRunner(generatorPath),
			initErrorSymbol: "IE(G)",
			errorHandlers: [
				newRunnerErrorHandler({
					accessErrorSymbol: "DNE(G)",
					compilationErrorSymbol: "CE(G)",
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
	const [generator, checker, solution] = initResult.results;

	return testTogether(
		[...keys, ...randomUnsigneds(n)],
		async (key: number): Promise<TestCaseResult> => {
			const checkerInput = new PassThrough();
			const checkerOutput = new WritableString();
			const input = new PassThrough();

			// `{ end: false }` prevents the pipee from ending when the piper does.
			// Ensures the checker doesn't end before reading the solution's output
			// first.
			input.pipe(checkerInput, { end: false });

			// TODO: Make it so that outputs also go to a folder/file to be reviewed
			// later.
			let result = await runTogether([
				{
					promise: generator.run({
						stdin: Readable.from(`${key}`),
						stdout: input,
					}),
					runtimeErrorVerdictSymbol: "RE(G)",
				},
				{
					promise: checker.run({
						stdin: checkerInput,
						stderr: checkerOutput,
					}),
					runtimeErrorVerdictSymbol: "RE(C)",
				},
				{
					promise: solution.run({
						stdin: input,
						stdout: checkerInput,
					}),
					runtimeErrorVerdictSymbol: "RE",
				},
			]);

			if (!result && checkerOutput.string) {
				result = {
					passed: false,
					verdictSymbol: "WA",
					reason: checkerOutput.string,
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
