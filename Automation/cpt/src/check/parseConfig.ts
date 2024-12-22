import ini from "ini";
import { testSetSchema } from "./schemas";
import { TestSet, TestSetParsingError } from "./types";

export default (configString: string) => {
	const config = ini.parse(configString);

	const testSets: TestSet[] = [],
		errors: TestSetParsingError[] = [];
	function dfs(object: typeof config, fullKey: string = ""): void {
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
			} else dfs(object[key], fullKey.length === 0 ? key : `${fullKey}.${key}`);
		}

		if (hasConfig && fullKey.length > 0) {
			const { success, error, data } = testSetSchema.safeParse({
				name: fullKey,
				config: object,
			});
			if (!success) {
				errors.push({
					name: fullKey,
					error,
				});
				return;
			}

			testSets.push(data);
		}
	}
	dfs(config);

	return {
		testSets,
		errors,
	};
};
