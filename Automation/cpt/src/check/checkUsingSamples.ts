import fs from "fs";
import { SamplesTestSet, TestSetResult } from "./types";

export default async ({
	name,
	config: { checker },
}: SamplesTestSet): Promise<TestSetResult> => {
	if (!fs.existsSync("inputs"))
		throw { error: "sample inputs folder `inputs` does not exist" };

	if (checker) {
		if (!fs.existsSync(checker))
			throw { error: `checker \`${checker}\` does not exist` };

		return {
			name,
			testCaseResults: [],
		};
	} else {
		if (!fs.existsSync("outputs"))
			throw { error: "sample outputs folder `outputs` does not exist" };

		return {
			name,
			testCaseResults: [],
		};
	}
};
