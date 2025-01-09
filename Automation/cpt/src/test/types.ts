import z from "zod";
import { Result } from "../utils/errors";

export const generatorTestSetSchema = z.object({
	name: z.string(),
	generatorPath: z.string(),
	generatorLanguage: z.string().optional(),
	checkerPath: z.string(),
	checkerLanguage: z.string().optional(),
	randomKeys: z.number().optional(),
	keys: z.number().array().optional(),
});

export const interactorTestSetSchema = z.object({
	name: z.string(),
	interactorPath: z.string(),
	interactorLanguage: z.string().optional(),
	randomKeys: z.number().optional(),
	keys: z.number().array().optional(),
});

export const samplesTestSetSchema = z.object({
	name: z.string(),
	useSamples: z.literal(true),
	checkerPath: z.string().optional(),
	checkerLanguage: z.string().optional(),
});

export const testSetSchema = z.union([
	generatorTestSetSchema,
	interactorTestSetSchema,
	samplesTestSetSchema,
]);

export type GeneratorTestSet = z.infer<typeof generatorTestSetSchema>;
export type InteractorTestSet = z.infer<typeof interactorTestSetSchema>;
export type SamplesTestSet = z.infer<typeof samplesTestSetSchema>;
export type TestSet = z.infer<typeof testSetSchema>;

export type Context = {
	solutionPath: string;
	solutionLanguage?: string;
};

export type TestCaseResult = {
	verdict: string;
	reason?: any;
};

export type TestSetResult = {
	initResults: Record<string, ResultWithVerdict<any>>;
	// For cases with generated input, the corresponding key must be integer-
	// parsable to seed the generator.
	caseResults?: Record<string, TestCaseResult>;
};

export type TesterModule<T extends TestSet> = (
	context: Context,
	testSet: T
) => Promise<TestSetResult>;

export type ResultWithVerdict<T> = Result<T> & { verdict: string };
