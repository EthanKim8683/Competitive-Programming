import quote from "../../../utils/quote";

export default (got: string, expected: string): string | undefined => {
	const gotTokens = got.trim().split(/\s+/g),
		expectedTokens = expected.trim().split(/\s+/g);

	for (let i = 0; i < Math.max(gotTokens.length, expectedTokens.length); i++) {
		const getToken = (array: string[], index: number): string =>
			index >= array.length ? "EOF" : quote(array[index]);

		const gotToken = getToken(gotTokens, i),
			expectedToken = getToken(expectedTokens, i);
		if (gotToken != expectedToken)
			return `Expected ${expectedToken}, got ${gotToken}`;
	}
};
