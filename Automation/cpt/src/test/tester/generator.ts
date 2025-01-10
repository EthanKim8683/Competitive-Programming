import { WritableString } from "../../utils/stream";
import { initTogether, runTogether, program, testTogether } from "../tester";
import {
	Context,
	GeneratorTestSet,
	TesterModule,
	TestSetResult,
	Verdict,
} from "../types";
import { randomUnsigneds } from "../utils";

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
	const { verdicts: initVerdicts, results } = await initTogether([
		["s", program(solutionPath, solutionLanguage)],
		["g", program(generatorPath, generatorLanguage)],
		["c", program(checkerPath, checkerLanguage)],
	]);

	if (!results) return { initVerdicts };
	const [solution, generator, checker] = results;

	async function runTestCase(key: number): Promise<Verdict> {
		const solutionProcess = solution(),
			generatorProcess = generator(),
			checkerProcess = checker();

		const checkerWritable = new WritableString();

		generatorProcess.stdin.write(`${key}\n`);
		generatorProcess.stdout.pipe(checkerProcess.stdin, { end: false });
		generatorProcess.stdout.pipe(solutionProcess.stdin);

		generatorProcess.promise.then(() => {
			checkerProcess.stdin.write("\n");
			solutionProcess.stdout.pipe(checkerProcess.stdin);
			checkerProcess.stderr.pipe(checkerWritable);
		});

		const verdict = await runTogether([
			["g", generatorProcess],
			["s", solutionProcess],
			["c", checkerProcess],
		]);
		if (verdict) return verdict;

		if (checkerWritable.string)
			return { symbol: "WA", reason: checkerWritable.string };

		return { symbol: "OK" };
	}

	const caseVerdicts = await testTogether(
		[...keys, ...randomUnsigneds(randomKeys)],
		runTestCase
	);

	return { initVerdicts, caseVerdicts };
};
export default generator;
