import crypto from "crypto";
import fs from "fs";
import path from "path";
import os from "os";
import esMain from "es-main";

import compile from "./compile.js";
import { quoteForPrint } from "./utils.js";

export default async function compileWithCache(progPath, lang, force = false) {
	const { promise, resolve, reject } = Promise.withResolvers();

	const hash = crypto.createHash("sha256");
	hash.update("" + lang);

	const stream = fs.createReadStream(progPath);

	stream.on("error", (err) =>
		reject(`Error reading from program ${quoteForPrint(progPath)}`, {
			cause: err,
		})
	);
	stream.on("data", (data) => hash.update(data));
	stream.on("close", () => {
		const fp = hash.digest("hex").split(" ")[0];
		const exePath = path.join(os.tmpdir(), fp);

		fs.promises
			.access(exePath)
			.then(() => true)
			.catch(() => false)
			.then((exists) => {
				if (!exists || force) {
					return compile(progPath, exePath, lang);
				}
			})
			.then(() => resolve(exePath));
	});

	return promise;
}

if (esMain(import.meta)) {
	const rv = await compileWithCache(...process.argv.slice(2));
	console.log(rv);
}
