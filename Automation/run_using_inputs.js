import fs from "fs";
import path from "path";
import esMain from "es-main";

import run from "./run.js";

export default function runUsingInputs(exePath, inputDir, series = false) {
	const { promise, resolve, reject } = Promise.withResolvers();

	function runUsingInput(inputFile) {
		const output = [];
		function append(from, data) {
			if (output.length > 0 && output.at(-1).from === from) {
				output.at(-1).data += data;
			} else {
				output.push({ from, data });
			}
		}

		return run(exePath, (stdin, stdout, stderr) => {
			fs.createReadStream(inputFile).pipe(stdin);
			stdout.on("data", (data) => append("stdout", data.toString()));
			stderr.on("data", (data) => append("stderr", data.toString()));
		}).then((rusage) => ({ rusage, output }));
	}

	fs.readdir(inputDir, async (err, files) => {
		if (err) {
			return reject(
				new Error("Error while reading input directory", { cause: err })
			);
		}

		files = files.map((file) => path.join(inputDir, file));
		let results;
		if (series) {
			results = [];
			for (const file of files) {
				results.push(await runUsingInput(file));
			}
		} else {
			results = await Promise.all(
				files.map(async (file) => runUsingInput(file))
			);
		}
		resolve(results);
	});

	return promise;
}

if (esMain(import.meta)) {
	const rv = await runUsingInputs(...process.argv.slice(2));
	console.log(rv);
}
