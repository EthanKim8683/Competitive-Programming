import assert from "assert";

import { createRunner } from "./run/util";
import { KillablePromise } from "./base";
import { ReadStreamProcess, SpawnProcess } from "./run/impl";

// KillablePromise.all([
// 	createRunner("inputs"),
// 	createRunner("check.cpp"),
// 	createRunner("sol.cpp"),
// ]).promise.then(([inputs, check, sol]) => {
// 	const inputsProc = inputs.run({ dirOptions: { basename: "1.txt" } });
// 	const checkProc = check.run({ spawnOptions: { stdio: ["pipe", "inherit"] } });
// 	const solProc = sol.run();
//
// 	assert(inputsProc instanceof ReadStreamProcess);
// 	assert(checkProc instanceof SpawnProcess);
// 	assert(solProc instanceof SpawnProcess);
//
// 	inputsProc.stream.pipe(checkProc.child.stdin!, { end: false });
// 	inputsProc.stream.pipe(solProc.child.stdin!);
// 	solProc.child.stdout!.pipe(checkProc.child.stdin!);
//
// 	KillablePromise.all([inputsProc, checkProc, solProc]);
// });

// KillablePromise.all([
// 	createRunner("gen.cpp"),
// 	createRunner("check.cpp"),
// 	createRunner("sol.cpp"),
// ]).promise.then(([gen, check, sol]) => {
// 	const genProc = gen.run();
// 	const checkProc = check.run({ spawnOptions: { stdio: ["pipe", "inherit"] } });
// 	const solProc = sol.run();
//
// 	assert(genProc instanceof SpawnProcess);
// 	assert(checkProc instanceof SpawnProcess);
// 	assert(solProc instanceof SpawnProcess);
//
// 	genProc.child.stdout!.pipe(checkProc.child.stdin!, { end: false });
// 	genProc.child.stdout!.pipe(solProc.child.stdin!);
// 	solProc.child.stdout!.pipe(checkProc.child.stdin!);
//
// 	KillablePromise.all([genProc, checkProc, solProc]);
// });

createRunner("inputs").promise.then((i) =>
	i.run({ dirOptions: { basename: "1.tx" } })
);
