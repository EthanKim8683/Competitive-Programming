export type IfIncludes<T extends any[], S, Then = true, Else = false> = {
	[U in keyof T]: T[U] extends S ? unknown : never;
}[number] extends never
	? Else
	: Then;
