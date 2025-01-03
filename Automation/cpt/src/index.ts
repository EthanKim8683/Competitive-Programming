import assert from "assert";

import { createRunner } from "./run/util";
import { KillablePromise } from "./base";
import { isDirRunner } from "./run/runners/dir";
import { SpawnProcess } from "./run/impl";

// KillablePromise.all([
// 	createRunner("inputs"),
// 	createRunner("check.cpp"),
// 	createRunner("sol.cpp"),
// ]).promise.then(([inputs, check, sol]) => {
// 	assert(isDirRunner(inputs));
//
// 	const inputsRun = inputs.run({ dirBasename: "1.txt" });
// 	const checkRun = check.run({
// 		spawnOptions: { stdio: [undefined, "inherit"] },
// 	});
// 	const solRun = sol.run();
//
// 	assert(checkRun instanceof SpawnProcess);
// 	assert(solRun instanceof SpawnProcess);
//
// 	inputsRun.stream.pipe(checkRun.child.stdin!, { end: false });
// 	inputsRun.stream.pipe(solRun.child.stdin!);
// 	solRun.child.stdout!.pipe(checkRun.child.stdin!);
//
// 	KillablePromise.all([inputsRun, checkRun, solRun]);
// });

KillablePromise.all([
	createRunner("gen.cpp"),
	createRunner("check.cpp"),
	createRunner("sol.cpp"),
]).promise.then(([inputs, check, sol]) => {
	const genRun = inputs.run();
	const checkRun = check.run({
		spawnOptions: { stdio: [undefined, "inherit"] },
	});
	const solRun = sol.run();

	assert(genRun instanceof SpawnProcess);
	assert(checkRun instanceof SpawnProcess);
	assert(solRun instanceof SpawnProcess);

	genRun.child.stdout!.pipe(checkRun.child.stdin!, { end: false });
	genRun.child.stdout!.pipe(solRun.child.stdin!);
	solRun.child.stdout!.pipe(checkRun.child.stdin!);

	KillablePromise.all([genRun, checkRun, solRun]);
});
