import z from "zod";

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
	key: number | string;
	passed: boolean;
	verdict: string;
	reason?: string;
};

// An "Errorlet" is an Error with a symbol. A TestSetError can contain multiple
// Errorlets for each error that occurred while initing.
export class TestSetErrorlet extends Error {
	// symbol and error are aliased to message and cause, respectively.
	constructor(symbol: string, error: Error) {
		super(symbol, { cause: error });
	}
}
export class TestSetError extends Error {
	// errorlets is aliased to cause.
	constructor(errorlets: TestSetErrorlet[]) {
		super(errorlets.map((errorlet) => errorlet.name).join(", "), {
			cause: errorlets,
		});
	}
}

export type TestSetResult = {
	testCases: TestCaseResult[];
};

export type TesterModule<T extends TestSet> = (
	context: Context,
	testSet: T
) => Promise<TestSetResult>;
