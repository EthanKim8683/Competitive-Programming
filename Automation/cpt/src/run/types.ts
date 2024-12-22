import { Readable, Writable } from "stream";
import { makeExecutor } from "./execute";

export enum StdioOption {
	STRING,
	INHERIT,
	IGNORE,
}

export type StdinOption = string | StdioOption.INHERIT | Readable;
export type StdoutOption = StdioOption | Writable;
export type StderrOption = StdioOption | Writable;

export type CompilationResult =
	| {
			success: true;
			warning?: string;
	  }
	| {
			success: false;
			error: string;
	  };

export type LanguageEntry = (filePath: string) => Promise<
	| {
			success: true;
			warning?: string;
			run: ReturnType<typeof makeExecutor>;
	  }
	| {
			success: false;
			error: string;
	  }
>;
