export type IfIncludes<
	Haystack extends any[],
	Needle,
	Then = true,
	Else = false,
> = {
	[I in keyof Haystack]: Haystack[I] extends Needle ? unknown : never;
}[number] extends never
	? Else
	: Then;

export type OmitFromReturnType<
	Function extends (...args: any[]) => any,
	Key extends keyof ReturnType<Function>,
> = (...args: Parameters<Function>) => Omit<ReturnType<Function>, Key>;
