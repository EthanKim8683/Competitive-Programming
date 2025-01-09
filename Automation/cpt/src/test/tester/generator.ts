import { Readable } from "stream";
import { randomUnsigneds } from "../../lib/js";
import { WritableString } from "../../lib/stream";
import program from "../../run/program";
import {
	Context,
	GeneratorTestSet,
	TestCaseResult,
	TesterModule,
	TestSetResult,
} from "../types";
import { initTogether, processTogether, testTogether } from "./util";

const generator: TesterModule<GeneratorTestSet> = async (
	{ solutionPath, solutionLanguage }: Context,
	{
		generatorPath,
		generatorLanguage,
		checkerPath,
		checkerLanguage,
		randomKeys = 0,
		keys = [],
	}: GeneratorTestSet
): Promise<TestSetResult> => {
	const initTogetherResult = await initTogether([
		{
			initer: program(solutionPath, solutionLanguage),
			symbol: "s",
			errorVerdict: "CE",
			warningVerdict: "CW",
		},
		{
			initer: program(generatorPath, generatorLanguage),
			symbol: "g",
			errorVerdict: "CE",
			warningVerdict: "CW",
		},
		{
			initer: program(checkerPath, checkerLanguage),
			symbol: "c",
			errorVerdict: "CE",
			warningVerdict: "CW",
		},
	] as const);

	const { initResults, success } = initTogetherResult;
	if (!success) return { initResults };
	const [solutionInvoker, generatorInvoker, checkerInvoker] =
		initTogetherResult.invokers;

	async function runTestCase(key: number): Promise<TestCaseResult> {
		const solutionProcess = solutionInvoker(),
			generatorProcess = generatorInvoker(),
			checkerProcess = checkerInvoker(),
			checkerWritable = new WritableString();

		Readable.from(`${key}`).pipe(generatorProcess.stdin);
		checkerProcess.stderr.pipe(checkerWritable);

		// { end: false } prevents checkerProcess.stdin from closing when
		// generatorProcess.stdout does.
		generatorProcess.stdout.pipe(checkerProcess.stdin, { end: false });
		generatorProcess.stdout.pipe(solutionProcess.stdin);

		let testCaseResult = await processTogether([
			{
				process: generatorProcess,
				symbol: "g",
				errorVerdict: "RE",
			},
		] as const);

		solutionProcess.stdout.pipe(checkerProcess.stdin);
		// Separate generator output from solution output in checker input.
		checkerProcess.stdin.write("\n");

		testCaseResult ??= await processTogether([
			{
				process: solutionProcess,
				symbol: "s",
				errorVerdict: "RE",
			},
			{
				process: checkerProcess,
				symbol: "c",
				errorVerdict: "RE",
			},
		] as const);

		if (testCaseResult) return testCaseResult;

		if (checkerWritable.string)
			return { verdict: "WA", reason: checkerWritable.string };

		return { verdict: "OK" };
	}

	const caseResults = await testTogether(
		[...keys, ...randomUnsigneds(randomKeys)],
		runTestCase
	);

	return {
		initResults,
		caseResults,
	};
};
export default generator;
