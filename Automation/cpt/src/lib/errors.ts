import z from "zod";

export const errorSchema = z.object({
	name: z.string(),
	message: z.string(),
});
// Assert that errorSchema matches Error while maintaining its type.
errorSchema as z.ZodType<Error>;

export const systemErrorSchema = errorSchema.extend({
	address: z.string().optional(),
	code: z.string(),
	dest: z.string().optional(),
	errno: z.number(),
	info: z.custom((value) => value instanceof Object),
	message: z.string(),
	path: z.string().optional(),
	port: z.number().optional(),
	syscall: z.string(),
});

export type SystemError = z.infer<typeof systemErrorSchema>;

export function isSystemError(value: any): value is SystemError {
	if (!(value instanceof Error)) return false;

	// Does value match SystemError in type?
	if (!systemErrorSchema.safeParse(value).success) return false;

	// Further checks probably won't be necessary.
	return true;
}
