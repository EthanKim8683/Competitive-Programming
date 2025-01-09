import z from "zod";

const errorSchema = z.object({
	name: z.string(),
	message: z.string(),
});
// Assert that errorSchema matches Error while preserving its type; .extend()
// does not exist on z.ZodType<Error>
errorSchema as z.ZodType<Error>;

const systemErrorSchema = errorSchema.extend({
	address: z.string().optional(),
	code: z.string(),
	dest: z.string().optional(),
	errno: z.number(),
	info: z.custom((value) => value instanceof Object).optional(),
	message: z.string(),
	path: z.string().optional(),
	port: z.number().optional(),
	syscall: z.string(),
});
export type SystemError = z.infer<typeof systemErrorSchema>;

export function isSystemError(value: any): value is SystemError {
	if (!(value instanceof Error)) return false;

	// The structure of SystemError is unique enough to filter out most good-faith
	// errors
	return systemErrorSchema.safeParse(value).success;
}

// https://medium.com/with-orus/the-5-commandments-of-clean-error-handling-in-ty
// pescript-93a9cbdf1af5

// Required to implement commandment #4:
export class ContextfulError extends Error {
	constructor(
		message: string,
		readonly context: Object,
		options?: ErrorOptions
	) {
		super(message, options);
	}
}

// Commandment #5:
export type Result<T, E extends Error = Error> =
	| { success: true; result: T }
	| { success: false; error: E };
