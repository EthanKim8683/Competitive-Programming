import { Readable, Writable } from "stream";
import { partial } from "./run";

export enum StdioOption {
	STRING,
	INHERIT,
	IGNORE,
}

export type StdinOption = string | StdioOption.INHERIT | Readable;
export type StdoutOption = StdioOption | Writable;
export type StderrOption = StdioOption | Writable;

type Args = {
	compileArgs?: string[];
	runArgs: string[];
};
export type LanguageEntry = (filePath: string) => Promise<Args> | Args;

export enum MakeRunnerError {
	ACCESS_ERROR = "could not access file",
	INFER_ERROR = "could not infer language",
	SUPPORT_ERROR = "unsupported language",
	COMPILE_ERROR = "could not compile file",
}

type MakeRunnerResultBase = {
	filePath: string;
};
type MakeRunnerResultAccessed = MakeRunnerResultBase & {};
type MakeRunnerResultInferred = MakeRunnerResultAccessed & { language: string };
type MakeRunnerResultSupports = MakeRunnerResultInferred &
	Awaited<ReturnType<LanguageEntry>>;
type MakeRunnerResultCompiled = MakeRunnerResultSupports & {
	warning?: string;
	run: ReturnType<typeof partial>;
};
export type UnsuccessfulMakeRunnerResult =
	| (MakeRunnerResultBase & {
			success: false;
			error: MakeRunnerError.ACCESS_ERROR;
			hint?: string;
	  })
	| (MakeRunnerResultAccessed & {
			success: false;
			error: MakeRunnerError.INFER_ERROR;
			hint?: string;
	  })
	| (MakeRunnerResultInferred & {
			success: false;
			error: MakeRunnerError.SUPPORT_ERROR;
			hint?: string;
	  })
	| (MakeRunnerResultSupports & {
			success: false;
			error: MakeRunnerError.COMPILE_ERROR;
			hint?: string;
	  });
export type SuccessfulMakeRunnerResult = MakeRunnerResultCompiled & {
	success: true;
};
export type MakeRunnerResult =
	| UnsuccessfulMakeRunnerResult
	| SuccessfulMakeRunnerResult;
