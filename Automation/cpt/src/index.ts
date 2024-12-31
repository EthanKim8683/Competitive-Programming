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

// import { PassThrough, Readable } from "stream";
// import Runner from "./run/Runner";
// import generator from "./test/testers/generator";
// import WritableString from "./stream/WritableString";
// import { spawn } from "child_process";
//
// (async () => {
// 	const generatorPath: string = "gen.cpp";
// 	const checkerPath: string = "check.cpp";
// 	const solutionPath: string = "sol.cpp";
//
// 	const g = new Runner(generatorPath);
// 	const c = new Runner(checkerPath);
// 	const s = new Runner(solutionPath);
//
// 	const gi = Readable.from("124\n");
// 	const go = new PassThrough();
// 	const ci = new PassThrough();
// 	const co = new WritableString();
// 	const i = new PassThrough();
// 	const o = new PassThrough();
//
// 	go.pipe(i);
// 	go.pipe(ci, { end: false });
// 	o.pipe(ci, { end: false });
//
// 	const o2 = new WritableString();
// 	o.pipe(o2);
//
// 	go.on("end", () => console.log("go"));
// 	o.on("end", () => console.log("o"));
// 	ci.on("end", () => console.log("ci"));
//
// 	await Promise.all([
// 		g.run({ stdin: gi, stdout: go }),
// 		c.run({ stdin: ci, stderr: co }),
// 		s.run({ stdin: i, stdout: o }),
// 	]);
//
// 	console.log(co.string);
// 	console.log(o2.string);
// })();

// import { PassThrough, Readable } from "stream";
// import WritableString from "./stream/WritableString";
//
// (async () => {
// 	const x = new PassThrough();
// 	const y = new PassThrough();
// 	const z = new WritableString();
//
// 	const a = Readable.from("a\n");
// 	const b = Readable.from("b\n");
// 	const p = new PassThrough();
// 	const q = new PassThrough();
// 	a.pipe(x);
// 	b.pipe(y);
// 	x.pipe(p);
// 	y.pipe(q);
// 	p.pipe(z);
// 	q.pipe(z);
// 	z.on("close", () => {
// 		console.log(z.string);
// 	});
// })();

// import Runner from "./run/Runner";
//
// (async () => {
// 	const runner = new Runner("sol.cpp");
//
// 	console.log(await runner.run());
// })().catch(() => {});
