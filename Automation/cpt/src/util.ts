export type ConstructorType<T extends new (...args: any[]) => any> = new (
	...args: ConstructorParameters<T>
) => T;

// https://stackoverflow.com/a/58765199/19662543
export type OmitFirstParameter<T> = T extends (
	arg0: any,
	...args: infer P
) => infer R
	? (...args: P) => R
	: never;

// https://stackoverflow.com/a/49285826/19662543
type OneOfImpl<
	T,
	V extends any[],
	NK extends keyof V = Exclude<keyof V, keyof any[]>,
> = { [K in NK]: T extends V[K] ? V[K] : never }[NK];
export type OneOf<T, V extends any[]> = OneOfImpl<T, V>;

export type ElementType<T extends any[]> = T extends (infer E)[] ? E : never;

// https://stackoverflow.com/a/69328045/19662543
export type Require<T, K extends keyof T> = T & { [P in K]-?: T[P] };

export function quote(string: string): string {
	// Most similar to how quote-containing strings are printed in Node.js.
	for (const char of [..."'`\""])
		if (!string.includes(char)) return `${char}${string}${char}`;
	return `'${string.replaceAll("'", "\\'")}'`;
}

// Whether to use .ts-like or .js-like file extensions when requiring code.
export const tj = process.env.TSX ? "t" : "j";
