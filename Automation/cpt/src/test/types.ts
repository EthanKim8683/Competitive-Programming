import {
	samplesTestSetSchema,
	generatorTestSetSchema,
	interactorTestSetSchema,
	testSetSchema,
} from "./schemas";
import z from "zod";

export type SamplesTestSet = z.infer<typeof samplesTestSetSchema>;
export type GeneratorTestSet = z.infer<typeof generatorTestSetSchema>;
export type InteractorTestSet = z.infer<typeof interactorTestSetSchema>;
export type TestSet = z.infer<typeof testSetSchema>;

export type TestSetParsingError = {
	name: string;
	error: z.ZodError;
};

export class TesterInitError extends Error {
	constructor(message: string, options?: ErrorOptions) {
		super(message, options);
	}
}

export enum TestCaseVerdict {
	OK = "OK",
	WRONG_ANSWER = "WA",
	RUNTIME_ERROR = "RE",
	TIME_LIMIT_EXCEEDED = "TLE",
	MEMORY_LIMIT_EXCEEDED = "MLE",
	GENERATOR_RUNTIME_ERROR = "GRE",
	CHECKER_RUNTIME_ERROR = "CRE",
	INTERACTOR_RUNTIME_ERROR = "IRE",
}

export type TestCaseResult = {
	key: number;
	verdict: TestCaseVerdict;
	hint?: string;
};

export type TestSetResult = {
	makeRunnerResults: MakeRunnerResult[];
} & (
	| {
			success: false;
	  }
	| {
			success: true;
			testCaseResults: TestCaseResult[];
	  }
);
