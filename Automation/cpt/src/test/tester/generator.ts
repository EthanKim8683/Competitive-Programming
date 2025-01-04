import { allFulfilled } from "../../lib/js";
import { KillablePromise } from "../../lib/KillablePromise";
import program from "../../run/program";
import {
	Context,
	GeneratorTestSet,
	TesterModule,
	TestSetResult,
} from "../types";
import { throwErrorlets } from "./util";

const generator: TesterModule<GeneratorTestSet> = async (
	{ solutionPath, solutionLanguage }: Context,
	{
		generatorPath,
		generatorLanguage,
		checkerPath,
		checkerLanguage,
	}: GeneratorTestSet
): Promise<TestSetResult> => {
	// Maybe write a util that pairs initers with symbols so that the lengths of
	// the two arrays must matcb?
	const [solutionInvoker, generatorInvoker, checkerInvoker] =
		await KillablePromise.allSettled([
			program(solutionPath, { language: solutionLanguage }),
			program(generatorPath, { language: generatorLanguage }),
			program(checkerPath, { language: checkerLanguage }),
		])
			.promise.then(allFulfilled)
			.catch(throwErrorlets(["CE", "CE(G)", "CE(C)"]));

	throw "Not implemented";
};
export default generator;
