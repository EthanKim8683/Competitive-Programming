import z from "zod";
import pathSchema from "./pathSchema";

export default z.object({
	name: z.string(),
	config: z.object({
		samples: z.literal(true),
		checker: pathSchema.optional(),
	}),
});
