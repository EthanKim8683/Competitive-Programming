import { glob } from "glob";
import makeRunner from "../run/makeRunner";

export default () =>
	(async () => {
		const solutionMatches = await glob("sol.*");
		if (solutionMatches.length === 0)
			throw { error: "could not find solution" };
		if (solutionMatches.length > 1) throw { error: "multiple solutions found" };
		const solution = solutionMatches[0];

		return makeRunner(solution);
	})().catch((err) => {
		throw { error: "failed to initialize solution", hint: err };
	});
