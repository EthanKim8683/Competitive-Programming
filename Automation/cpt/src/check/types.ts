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

export enum TestCaseVerdict {
	OK,
	WA,
	RE,
	TLE,
	MLE,
	GRE,
	CRE,
	IRE,
}

export type TestCaseResult = {
	index: number;
	key: number;
	verdict: TestCaseVerdict;
	log: string;
	time: number;
	memory: number;
};

export type TestSetResult = {
	name: string;
	testCaseResults: TestCaseResult[];
};
