import compile from "./compile";
import { makeExecutor } from "./execute";
import { LanguageEntry } from "./types";

export default (
	setup: (
		filePath: string
	) => Promise<{ compile?: string[]; execute?: string[] }>
): LanguageEntry => {
	return async (filePath) => {
		const { compile: compileArgs, execute: executeArgs } =
			await setup(filePath);

		const compileResult = await compile(compileArgs ?? []);
		if (!compileResult.success) return compileResult;

		return {
			...compileResult,
			run: makeExecutor(executeArgs ?? []),
		};
	};
};
