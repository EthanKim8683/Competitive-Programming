import z from "zod";

const errorSchema = z.object({
	name: z.string(),
	message: z.string(),
});
// Assert that `errorSchema` is satisfactory while maintaining its type.
errorSchema as z.ZodType<Error>;
const objectInstanceSchema: z.ZodType<Object> = z.record(z.any(), z.any());

const systemErrorSchema = errorSchema.extend({
	address: z.string().optional(),
	code: z.string(),
	dest: z.string().optional(),
	errno: z.number(),
	info: objectInstanceSchema.optional(),
	message: z.string(),
	path: z.string().optional(),
	port: z.number().optional(),
	syscall: z.string(),
});
export type SystemError = z.infer<typeof systemErrorSchema>;

export default (value: any): value is SystemError => {
	if (!(value instanceof Error)) return false;

	// Does `value` satisfy `SystemError` type-wise?
	if (
		!((value: Error): value is SystemError =>
			systemErrorSchema.safeParse(value).success)(value)
	)
		return false;

	// Further checks probably won't be necessary.
	return true;
};
