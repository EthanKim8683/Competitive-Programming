import { PassThrough } from "stream";
import WritableString from "../../stream/WritableString";
import InteractorTestSet from "../types/InteractorTestSet";
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
	{ config: { interactor: interactorPath, n, keys } }: InteractorTestSet
): Promise<TestSetResult> => {
	const initResult = await initTogether([
		newRunner([interactorPath], {
			default: "IE(I)",
			accessError: "DNE(I)",
			compilationError: "CE(I)",
		}),
		newRunner([solutionPath], {
			default: "IE",
			accessError: "DNE",
			compilationError: "CE",
		}),
	]);

	if (!initResult.success) return initResult;
	const [interactor, solution] = initResult.result;

	return testTogether(
		[...keys, ...randomUnsigneds(n)],
		async (key: number): Promise<TestCaseResult> => {
			const interactorInput = new PassThrough();
			const interactorOutput = new WritableString();
			const input = new PassThrough();
			const output = new PassThrough();
			interactorInput.write(`${key}\n`);
			output.pipe(interactorInput);

			const runResult = await runTogether([
				runRunner(
					interactor.run({
						stdin: interactorInput,
						stdout: input,
						stderr: interactorOutput,
					}),
					{ default: "?(I)", runtimeError: "RE(I)" }
				),
				runRunner(solution.run({ stdin: input, stdout: output }), {
					default: "?",
					runtimeError: "RE",
				}),
			]);

			if (!runResult.success)
				return { passed: false, reasons: runResult.reasons };

			if (interactorOutput.string)
				return { passed: false, reasons: { WA: interactorOutput.string } };

			return { passed: true };
		}
	);
};
