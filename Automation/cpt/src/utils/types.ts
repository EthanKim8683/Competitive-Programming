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
