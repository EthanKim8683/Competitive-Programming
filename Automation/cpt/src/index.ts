/* import parseConfig from "./check/parseConfig";

console.log(
  JSON.stringify(
    parseConfig(
      `[edge case 1]
generator="path.js"
checker="path.js"
n=10

[edge case 1.special]
generator="path.js"
checker="path.js"
n=100
keys[]=10
keys[]=134

[sample cases]
samples`
    ),
    null,
    2
  )
); */

/* import makeRunner from "./run/makeRunner";

(async () => {
	const run = await makeRunner("demo.c++20.cpp");
	await run();
})().catch((e) => console.error(e)); */

import checkUsingGenerator from "./check/checkUsingGenerator";

(async () => {
	await checkUsingGenerator({
		name: "test",
		config: {
			keys: [],
			n: 10,
			generator: "generator.c++17.cpp",
			checker: "checker.c++20.cpp",
		},
	});
})().catch((e) => console.error(JSON.stringify(e, null, 2)));
