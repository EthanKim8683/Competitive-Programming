import { createRunner } from "./run/util";

Promise.all([
	createRunner("sol.cpp").promise,
	createRunner("check.cpp").promise,
	createRunner("gen.cpp").promise,
])
	.then((rs) => {
		console.log("!");
		return rs;
	})
	.then((rs) => Promise.all(rs.map((r) => r.run?.()?.promise)))
	.then(() => console.log("!"));
