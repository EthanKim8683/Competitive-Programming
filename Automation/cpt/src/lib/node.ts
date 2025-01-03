import z from "zod";

export const promiseSchema: z.ZodType<Promise<any>> = z.instanceof(Promise);

export function isPromise(value: any | Promise<any>): value is Promise<any> {
	return promiseSchema.safeParse(value).success;
}
