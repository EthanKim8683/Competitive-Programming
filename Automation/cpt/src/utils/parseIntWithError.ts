import quote from "./quote";

function isInvalidRadix(radix?: number): boolean {
	return radix !== undefined && (radix < 2 || radix > 36);
}

export class ParseIntError extends Error {
	constructor(
		readonly string: string,
		readonly radix?: number
	) {
		super(
			isInvalidRadix(radix)
				? `Could not parse int using radix: ${radix}`
				: `Could not parse int using string: ${quote(string)}`
		);
	}
}

export default (string: string, radix?: number): number => {
	const number = parseInt(string, radix);
	if (isInvalidRadix(radix) || isNaN(number))
		throw new ParseIntError(string, radix);
	return number;
};
