import { assert } from "console";
import { WritableString } from "../../lib/stream";
import program from "../../run/program";
import readDir from "../../run/readDir";
import { quote } from "../../utils";
import {
	Context,
	SamplesTestSet,
	TestCaseResult,
	TesterModule,
	TestSetResult,
} from "../types";
import { initTogether, processTogether, testTogether } from "./util";

// Crappy diff checker, similar to the one CodeForces uses.
// TODO: Replace with more sophisticated/informative checker.
function diffChecker(expected: string, got: string): string | undefined {
	const expectedTokens = expected.trim().split(/\s+/g),
		gotTokens = got.trim().split(/\s+/g);

	function getToken(tokens: string[], index: number): string {
		return index >= tokens.length ? "EOF" : quote(tokens[index]);
	}

	for (let i = 0; ; i++) {
		const expectedToken = getToken(expectedTokens, i),
			gotToken = getToken(gotTokens, i);
		if (expectedToken != gotToken)
			return `Expected ${expectedToken}, got ${gotToken}`;

		if (expectedToken === "EOF") return;
	}
}

type SamplesTestSetWithChecker = Omit<SamplesTestSet, "checkerPath"> & {
	checkerPath: string;
};
type SamplesTestSetWithoutChecker = Omit<SamplesTestSet, "checkerPath"> & {
	checkerPath: undefined;
};

async function withChecker(
	{ solutionPath, solutionLanguage }: Context,
	{ checkerPath, checkerLanguage }: SamplesTestSetWithChecker
): Promise<TestSetResult> {
	throw "";
}

async function withoutChecker(
	{ solutionPath, solutionLanguage }: Context,
	_testSet: SamplesTestSetWithoutChecker
): Promise<TestSetResult> {
	const initTogetherResult = await initTogether([
		{
			initer: program(solutionPath, solutionLanguage),
			symbol: "s",
			errorVerdict: "CE",
			warningVerdict: "CW",
		},
		{
			initer: readDir("inputs"),
			symbol: "i",
			errorVerdict: "DE",
		},
		{
			initer: readDir("outputs"),
			symbol: "o",
			errorVerdict: "DE",
		},
	]);

	const { initResults, success } = initTogetherResult;
	if (!success) return { initResults };
	const [solutionInvoker, inputsInvoker, outputsInvoker] =
		initTogetherResult.invokers;

	// TODO: Handle case when input and output files don't match.

	async function runTestCase(key: string): Promise<TestCaseResult> {
		const solutionProcess = solutionInvoker.invoke(),
			inputsProcess = inputsInvoker.invoke(key),
			outputsProcess = outputsInvoker.invoke(key),
			solutionWritable = new WritableString(),
			outputsWritable = new WritableString();

		inputsProcess.stdout.pipe(solutionProcess.stdin);
		solutionProcess.stdout.pipe(solutionWritable);
		outputsProcess.stdout.pipe(outputsWritable);

		const testCaseResult = await processTogether([
			{
				process: solutionProcess,
				symbol: "s",
				errorVerdict: "RE",
			},
		] as const);

		if (testCaseResult) return testCaseResult;

		const diffCheckerResult = diffChecker(
			outputsWritable.string,
			solutionWritable.string
		);
		if (diffCheckerResult) return { verdict: "WA", reason: diffCheckerResult };

		return { verdict: "OK" };
	}

	const caseResults = await testTogether(
		inputsInvoker.fileBasenames,
		runTestCase
	);

	return {
		initResults,
		caseResults,
	};
}

const samples: TesterModule<SamplesTestSet> = async (
	context: Context,
	testSet: SamplesTestSet
): Promise<TestSetResult> => {
	// Assume useSamples is true.
	assert(testSet.useSamples);

	const testSetAsUnion = testSet as
		| SamplesTestSetWithChecker
		| SamplesTestSetWithoutChecker;
	return testSetAsUnion.checkerPath === undefined
		? withoutChecker(context, testSetAsUnion)
		: withChecker(context, testSetAsUnion);
};
export default samples;
