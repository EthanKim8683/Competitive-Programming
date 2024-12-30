import generator from "./test/testers/generator";
import GeneratorTestSet from "./test/types/GeneratorTestSet";

(async () => {
	const solutionPath: string = "sol.cpp";
	const generatorPath: string = "gen.cpp";
	const checkerPath: string = "check.cpp";
	const generatorTestSet: GeneratorTestSet = {
		name: "demo!! 🤞🤞",
		config: {
			generator: generatorPath,
			checker: checkerPath,
			n: 10,
			keys: [1337, 6969, 420],
		},
	};

	console.log(await generator(solutionPath, generatorTestSet));
})();
