import { PassThrough, Readable } from "stream";
import WritableString from "../../stream/WritableString";

export default async (
	solutionPath: string,
	{
		config: { generator: generatorPath, checker: checkerPath, n, keys },
	}: GeneratorTestSet
) => {
	try {
		const [generator, checker, solution] = await initTogether([
			initGeneratorUsing(newRunner(generatorPath)),
			initCheckerUsing(newRunner(checkerPath)),
			initSolutionUsing(newRunner(solutionPath)),
		]);
	} catch (err) {
		// Initers themselves filter out errors to handle and propogate them here.
		// This allows real errors to throw, while "pretend" errors become results.
		if (!(err instanceof TesterInitError)) throw err;
		return err.toTestSetResult();
	}

	// Still a little iffy on this? I guess it would still work with input/output
	// files...
	return testTogether(
		[...keys, randomUnsigneds(n)],
		async (key: number): TestCaseResult => {
			const input = new PassThrough();
			const checkerInput = new PassThrough();
			const checkerOutput = new WritableString();
			input.pipe(checkerInput);

			try {
				await runTogether([
					runGeneratorUsing(
						generator.run({ stdin: Readable.from(""), stdout: input })
					),
					runCheckerUsing(
						checker.run({ stdin: checkerInput, stdout: checkerOutput })
					),
					runSolutionUsing(
						solution.run({ stdin: input, stdout: checkerOutput })
					),
				]);
			} catch (err) {
				if (!(err instanceof TesterRuntimeError)) throw err;
				return err.toTestCaseResult();
			}

			if (checkerOutput.string) {
				const verdict = TestCaseVerdict.WRONG_ANSWER;
			}

			const verdict = TestCaseVerdict.OK;
		}
	);
};
