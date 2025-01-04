import assert from "assert";
import { PromiseSettledResults } from "../../lib/js";
import { TestSetError, TestSetErrorlet } from "../types";

export const throwErrorlets =
	(symbols: string[]) =>
	<T extends readonly any[]>(results: PromiseSettledResults<T>): never => {
		assert(symbols.length === results.length);

		const errorlets: TestSetErrorlet[] = [];
		results.forEach((result, index) => {
			if (result.status === "fulfilled") return;

			errorlets.push(new TestSetErrorlet(symbols[index], result.reason));
		});
		throw new TestSetError(errorlets);
	};
