import z from "zod";
import pathSchema from "./pathSchema";

export default z.object({
	name: z.string(),
	config: z.object({
		generator: pathSchema,
		checker: pathSchema,
		n: z.coerce.number().default(0),
		keys: z.coerce.number().array().default([]),
	}),
});
