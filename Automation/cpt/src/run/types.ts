import { partial } from "./run";

type LanguageEntryArgs = {
	compileArgs?: string[];
	runArgs: string[];
};
export type LanguageEntry = (
	filePath: string
) => Promise<LanguageEntryArgs> | LanguageEntryArgs;

export type Runner = ReturnType<typeof partial>;

export type MakeRunnerResult =
	| {
			success: false;
			error: any;
	  }
	| {
			success: true;
			warning?: string;
			run: Runner;
	  };
