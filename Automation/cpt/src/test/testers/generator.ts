import { PassThrough, Readable } from "stream";
import GeneratorTestSet from "../types/GeneratorTestSet";
import initTogether from "../tester/helpers/initTogether";
import runTogether from "../tester/helpers/runTogether";
import testTogether from "../tester/helpers/testTogether";
import WritableString from "../../stream/WritableString";
import newRunner from "../tester/utils/newRunner";
import randomUnsigneds from "../tester/utils/randomUnsigneds";
import TestCaseResult from "../tester/types/TestCaseResult";
import TestSetResult from "../tester/types/TestSetResult";

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
			runnerAccessErrorSymbol: "DNE(G)",
			runnerCompilationErrorSymbol: "CE(G)",
		},
		{
			promise: newRunner(checkerPath),
			initErrorSymbol: "IE(C)",
			runnerAccessErrorSymbol: "DNE(C)",
			runnerCompilationErrorSymbol: "CE(C)",
		},
		{
			promise: newRunner(solutionPath),
			initErrorSymbol: "IE",
			runnerAccessErrorSymbol: "DNE",
			runnerCompilationErrorSymbol: "CE",
		},
	]);

	if (!initResult.success)
		return {
			success: false,
			errorSymbols: initResult.errorSymbols,
		};
	const [generator, checker, solution] = initResult.results;

	return testTogether(
		[...keys, ...randomUnsigneds(n)],
		async (key: number): Promise<TestCaseResult> => {
			const input = new PassThrough();
			const checkerInput = new PassThrough();
			const checkerStdout = new WritableString();
			const checkerStderr = new WritableString();
			input.pipe(checkerInput);

			let result = await runTogether([
				{
					promise: generator.run({
						stdin: Readable.from(`${key}`),
						stdout: input,
					}),
					runtimeErrorVerdict: "RE(G)",
				},
				{
					promise: checker.run({
						stdin: checkerInput,
						stdout: checkerStdout,
						stderr: checkerStderr,
					}),
					runtimeErrorVerdict: "RE(C)",
				},
				{
					promise: solution.run({
						stdin: input,
						stderr: checkerInput,
					}),
					runtimeErrorVerdict: "RE",
				},
			]);

			if (!result && checkerStderr.string) {
				result = {
					passed: false,
					verdict: "WA",
					reason: checkerStderr.string,
				};
			}

			if (!result) {
				result = {
					passed: true,
					verdict: "OK",
					reason: checkerStdout.string,
				};
			}

			return result;
		}
	);
};
