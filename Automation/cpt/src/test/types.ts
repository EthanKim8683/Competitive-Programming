import z from "zod";

export const generatorTestSetSchema = z.object({
	generatorPath: z.string(),
	generatorLanguage: z.string().optional(),
	checkerPath: z.string(),
	checkerLanguage: z.string().optional(),
	randomKeys: z.number().optional(),
	keys: z.number().array().optional(),
});

export const interactorTestSetSchema = z.object({
	interactorPath: z.string(),
	interactorLanguage: z.string().optional(),
	randomKeys: z.number().optional(),
	keys: z.number().array().optional(),
});

export const samplesTestSetSchema = z.object({
	useSamples: z.literal(true),
	checkerPath: z.string().optional(),
	checkerLanguage: z.string().optional(),
});

export type GeneratorTestSet = z.infer<typeof generatorTestSetSchema>;
export type InteractorTestSet = z.infer<typeof interactorTestSetSchema>;
export type SamplesTestSet = z.infer<typeof samplesTestSetSchema>;

export type TestCaseResult = {
	passed: boolean;
	verdict: string;
	reason?: string;
};

// Perhaps a TestSetError?
export class TestSetError extends Error {}

export type TestSetResult = {
	testCases: TestCaseResult[];
};
