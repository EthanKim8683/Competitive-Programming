import program from "./run/program";
import { KillablePromise, KillablePromises } from "./lib/KillablePromise";
import { allFulfilled } from "./lib/js";
import generator from "./test/tester/generator";
import samples from "./test/tester/samples";
import { inspect } from "util";

// (async () => {
// 	console.log("Initing!");
//
// 	const [g, c, s] = await KillablePromise.all([
// 		program("gen.cpp"),
// 		program("check.cpp"),
// 		program("sol.cpp"),
// 	] as const).promise;
//
// 	console.log("Invoking!");
//
// 	const gp = g.invoke();
// 	const cp = c.invoke({ spawnOptions: { stdio: ["pipe", "inherit"] } });
// 	const sp = s.invoke();
//
// 	gp.stdout.pipe(sp.stdin);
// 	gp.stdout.pipe(cp.stdin, { end: false });
// 	sp.stdout.pipe(cp.stdin);
//
// 	await KillablePromise.all([gp, cp, sp] as const).promise;
//
// 	console.log("Done!");
// })();

(async () => {
	const r = await generator(
		{ solutionPath: "sol.cpp" },
		{
			name: "demo",
			generatorPath: "gen.cpp",
			checkerPath: "check.cpp",
			randomKeys: 10,
		}
	);

	console.log(r);
})();

// (async () => {
// 	const r = await samples(
// 		{ solutionPath: "sol.cpp" },
// 		{
// 			name: "demo",
// 			useSamples: true,
// 		}
// 	);
//
// 	console.log(inspect(r, { depth: 4 }));
// })();

// (async () => {
// 	const { promise, resolve, reject } = Promise.withResolvers();
// 	reject();
// 	promise.catch(() => console.log("Caught!"));
//
// 	const { promise, reject } = Promise.withResolvers();
// 	const killablePromise = new KillablePromise(promise);
// 	promise.catch();
// 	reject();
// 	Promise.resolve(killablePromise.promise).catch(() => console.log("Caught!"));
//
// 	const t = (): Promise<void> => {
// 		const { promise, reject } = Promise.withResolvers<void>();
// 		setTimeout(() => reject("Does the error persist?"), 1_000);
// 		return promise;
// 	};
// 	// t();
// 	// t().catch(() => {});
// 	function deactivatePromise<T>(promise: Promise<T>): Promise<T> {
// 		promise.catch(() => {});
// 		return promise;
// 	}
// 	const d = deactivatePromise(t());
// 	d.catch((err) => console.log(err));
// })();
