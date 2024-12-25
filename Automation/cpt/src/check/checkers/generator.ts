import { GeneratorTestSet, TestSetResult, TestCaseVerdict } from "../types";
import makeRunners from "../utils/makeRunners";
import { PassThrough } from "stream";
import fs from "fs";
import { StdioOption } from "../../run/types";
import randomUnsigned from "../../utils/randomUnsigned";

export default async (
	solutionPath: string,
	testSet: GeneratorTestSet
): TestSetResult => {
	const {
		config: { generator: generatorPath, checker: checkerPath, n, keys },
	} = testSet;

	const base = testSet;

	const { success, results: makeRunnersResult } = await makeRunners([
		generatorPath,
		checkerPath,
		solutionPath,
	]);

	const madeRunners = {
		...base,
		makeRunnersResult,
	};

	if (!success) {
		return {
			...madeRunners,
			success: false,
		};
	}

	const [generator, checker, solution] = makeRunnersResult.map(
		(result) => result.run
	);

	async function runTestCase(key: number) {
		const generatorStdout = new PassThrough();
		const checkerStdin = new PassThrough();

		checkerStdin.write(`${key}\n`);
		generatorStdout.pipe(checkerStdin);

		const generatorAborter = new AbortController();
		const checkerAborter = new AbortController();
		const solutionAborter = new AbortController();
		let aborted = false;
		function abort() {
			if (aborted) return;
			aborted = true;

			generatorAborter.abort();
			checkerAborter.abort();
			solutionAborter.abort();
		}

		let verdict, code, signal, time, memory;
		await Promise.all([
			(async () => {
				({ code, signal } = await generator({
					stdin: `${key}\n`,
					stdout: [generatorStdout] as const,
					stderr: [StdioOption.STRING] as const,
					aborter: generatorAborter,
				}));

				if ((code !== 0 || signal) && !verdict) {
					abort();
					verdict = TestCaseVerdict.GENERATOR_RUNTIME_ERROR;
					return;
				}

				({ code, signal, time, memory } = await solution({
					stdin: generatorStdout,
					stdout: [checkerStdin] as const,
					stderr: [StdioOption.STRING] as const,
					aborter: solutionAborter,
				}));

				if ((code !== 0 || signal) && !verdict) {
					abort();
					verdict = TestCaseVerdict.RUNTIME_ERROR;
					return;
				}
			})(),
			(async () => {
				({ code, signal } = await checker({
					stdin: checkerStdin,
					stdout: [StdioOption.STRING] as const,
					stderr: [StdioOption.STRING] as const,
					aborter: checkerAborter,
				}));

				if ((code !== 0 || signal) && !verdict) {
					abort();
					verdict = TestCaseVerdict.CHECKER_RUNTIME_ERROR;
					return;
				}
			})(),
		]);
	}

	const promises = [];
	for (let i = 0; i < n; i++) {
		promises.push(runTestCase(randomUnsigned()));
	}
	for (const key of keys) {
		promises.push(runTestCase(key));
	}
};
