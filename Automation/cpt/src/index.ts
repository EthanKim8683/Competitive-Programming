import program from "./run/program";
import { KillablePromise } from "./lib/KillablePromise";

(async () => {
	const [g, c, s] = await KillablePromise.all([
		program("gen.cpp"),
		program("check.cpp"),
		program("sol.cpp"),
	] as const).promise;

	const gp = g.invoke();
	const cp = c.invoke({ spawnOptions: { stdio: ["pipe", "inherit"] } });
	const sp = s.invoke();

	gp.stdout.pipe(sp.stdin);
	gp.stdout.pipe(cp.stdin, { end: false });
	sp.stdout.pipe(cp.stdin);

	await KillablePromise.all([gp, cp, sp] as const).promise;

	console.log("Done!");
})();
