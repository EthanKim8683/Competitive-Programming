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

export function quote(string: string): string {
	// Most similar to how quote-containing strings are printed in Node.js.
	for (const char of [..."'`\""])
		if (!string.includes(char)) return `${char}${string}${char}`;
	return `'${string.replaceAll("'", "\\'")}'`;
}

// Whether to use .ts-like or .js-like file extensions when requiring code.
export const tj = process.env.TSX ? "t" : "j";
