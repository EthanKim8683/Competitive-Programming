import ini from "ini";
import { testSetSchema } from "./schemas";
import { TestSet, TestSetParsingError } from "./types";

export default (configString: string) => {
	const config = ini.parse(configString);

	let solutionPath: string;
	const testSets: TestSet[] = [],
		errors: TestSetParsingError[] = [];
	function dfs(
		object: typeof config,
		path: string[] = [],
		root: boolean = true
	): void {
		const config: Record<string, any> = {};
		let hasConfig = false;
		for (const key in object) {
			if (
				typeof object[key] === "string" ||
				typeof object[key] === "boolean" ||
				Array.isArray(object[key])
			) {
				config[key] = object[key];
				hasConfig = true;
			} else dfs(object[key], path.concat([key]), false);
		}

		if (root) {
			// TODO: solutionPath, maybe other configs
			return;
		}

		if (hasConfig) {
			const name = path.join(".");
			const { success, error, data } = testSetSchema.safeParse({
				name,
				config: object,
			});
			if (success) testSets.push(data);
			else errors.push({ name, error });
		}
	}
	dfs(config);

	return {
		testSets,
		errors,
	};
};
