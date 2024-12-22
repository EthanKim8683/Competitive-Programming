import { GeneratorTestSet, TestCaseVerdict } from "./types";
import makeRunner from "../run/makeRunner";
import { Duplex, PassThrough } from "stream";
import { StdioOption } from "../run/types";
import makeSolutionRunner from "./makeSolutionRunner";
import makeRunners from "./makeRunners";
import randomUnsigned from "../utils/randomUnsigned";

export default async ({
	config: { generator, checker, n, keys },
}: GeneratorTestSet) => {
	const result = await makeRunners({
		generator: makeRunner(generator),
		checker: makeRunner(checker),
		solution: makeSolutionRunner(),
	});

	if (!result.success) {
		throw "";
	}
	const {
		generator: runGenerator,
		checker: runChecker,
		solution: runSolution,
	} = result.runners;

	async function runTestCase(key: number) {
		const generatorStdout = new PassThrough();
		const checkerStdin = new Duplex();

		checkerStdin.write(`${key}\n`);
		generatorStdout.pipe(checkerStdin);

		const generatorAborter = new AbortController();
		const checkerAborter = new AbortController();
		const solutionAborter = new AbortController();
		let verdict: TestCaseVerdict | undefined, code, signal;
		await Promise.all([
			(async () => {
				({ code, signal } = await runGenerator({
					stdin: `${key}\n`,
					stdout: generatorStdout,
					stderr: StdioOption.STRING,
					aborter: generatorAborter,
				}));
				if ((code !== 0 || signal) && !verdict) {
					checkerAborter.abort();
					verdict = TestCaseVerdict.GRE;
					return;
				}
				({ code, signal } = await runSolution({
					stdin: generatorStdout,
					stdout: checkerStdin,
					stderr: StdioOption.STRING,
					aborter: solutionAborter,
				}));
				if ((code !== 0 || signal) && !verdict) {
					checkerAborter.abort();
					verdict = TestCaseVerdict.RE;
				}
			})(),
			async () => {
				({ code, signal } = await runChecker({
					stdin: checkerStdin,
					stdout: StdioOption.STRING,
					stderr: StdioOption.STRING,
					aborter: checkerAborter,
				}));
				if ((code !== 0 || signal) && !verdict) {
					generatorAborter.abort();
					solutionAborter.abort();
					verdict = TestCaseVerdict.CRE;
				}
			},
		]);
	}

	const promises = [];
	for (let i = 0; i < n; i++) {
		promises.push(runTestCase(randomUnsigned()));
	}
	for (const key of keys) {
		promises.push(runTestCase(key));
	}
	await Promise.all(promises);
};
