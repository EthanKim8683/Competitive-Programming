import { PassThrough, Readable } from "stream";
import WritableString from "../../stream/WritableString";
import GeneratorTestSet from "../types/GeneratorTestSet";
import initTogether from "../tester/helpers/initTogether";
import runTogether from "../tester/helpers/runTogether";
import testTogether from "../tester/helpers/testTogether";
import newRunner from "../tester/utils/newRunner";
import runRunner from "../tester/utils/runRunner";
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
		newRunner([generatorPath], {
			default: "IE(G)",
			accessError: "DNE(G)",
			compilationError: "CE(G)",
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
	const [generator, checker, solution] = initResult.result;

	return testTogether(
		[...keys, ...randomUnsigneds(n)],
		async (key: number): Promise<TestCaseResult> => {
			const checkerInput = new PassThrough();
			const checkerOutput = new WritableString();
			const input = new PassThrough();

			// `{ end: false }` prevents the pipee from ending when the piper does.
			// Ensures the checker's input doesn't end before reading the solution's
			// output first.
			input.pipe(checkerInput, { end: false });

			// TODO: Make it so that outputs also go to a folder/file to be reviewed
			// later.
			const runResult = await runTogether([
				runRunner(
					generator.run({ stdin: Readable.from(`${key}`), stdout: input }),
					{ default: "?(G)", runtimeError: "RE(G)" }
				),
				runRunner(checker.run({ stdin: checkerInput, stderr: checkerOutput }), {
					default: "?(G)",
					runtimeError: "RE(C)",
				}),
				runRunner(solution.run({ stdin: input, stdout: checkerInput }), {
					default: "?",
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
};
