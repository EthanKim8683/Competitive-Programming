export function quote(string: string): string {
	// Most similar to how quote-containing strings are printed in Node.js
	for (const char of [..."'`\""])
		if (!string.includes(char)) return `${char}${string}${char}`;
	return `'${string.replaceAll("'", "\\'")}'`;
}
