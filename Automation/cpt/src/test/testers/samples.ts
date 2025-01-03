import { KillablePromise } from "../../base";
import { createRunner } from "../../run/util";
import { Require } from "../../util";
import {
	Context,
	SamplesTestSet,
	TestSetResult,
	TestSetTester,
} from "../types";

const usingChecker = async (
	{ solutionPath, solutionLanguage }: Context,
	{ checkerPath, checkerLanguage }: Require<SamplesTestSet, "checkerPath">
): Promise<TestSetResult> => {
	const allSettledResult = await KillablePromise.allSettled([
		createRunner("inputs", { language: "dir" }),
		createRunner(solutionPath, { language: solutionLanguage }),
		createRunner(checkerPath, { language: checkerLanguage }),
	]).promise;

	await KillablePromise.all([]).promise;

	throw "Not implemented";
};

const samplesTester: TestSetTester<SamplesTestSet> = async (
	context: Context,
	testSet: SamplesTestSet
): Promise<TestSetResult> => {
	const { checkerPath } = testSet;
	if (checkerPath) return usingChecker(context, { ...testSet, checkerPath });
	throw "Not implemented";
};
export default samplesTester;
