import z from "zod";
import isValidPath from "is-valid-path";

export const pathSchema = z.string().refine((path) => isValidPath(path), {
	message: "Invalid path",
});

export const samplesTestSetSchema = z.object({
	name: z.string(),
	config: z.object({
		samples: z.literal(true),
		checker: pathSchema.optional(),
	}),
});

export const generatorTestSetSchema = z.object({
	name: z.string(),
	config: z.object({
		generator: pathSchema,
		checker: pathSchema,
		n: z.coerce.number().default(0),
		keys: z.coerce.number().array().default([]),
	}),
});

export const interactorTestSetSchema = z.object({
	name: z.string(),
	config: z.object({
		interactor: pathSchema,
		n: z.coerce.number().default(0),
		keys: z.coerce.number().array().default([]),
	}),
});

export const testSetSchema = z.union([
	samplesTestSetSchema,
	generatorTestSetSchema,
	interactorTestSetSchema,
]);
