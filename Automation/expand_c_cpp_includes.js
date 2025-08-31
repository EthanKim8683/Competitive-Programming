import fs from "fs";
import readline from "readline";
import path from "path";
import esMain from "es-main";

import { quoteForPrint } from "./utils.js";

const includeDir = path.join(import.meta.dirname, "../include");

export default async function expandCCppIncludes(progPath) {
	const included = new Map();

	function getIncludePath(to, from) {
		const dir = to[0] === "." ? path.dirname(from) : includeDir;
		return path.join(dir, to);
	}

	function includeFile(file, filePath) {
		if (included.has(file)) return Promise.resolve();
		const data = { content: "", adj: [] };
		included.set(file, data);

		const { promise, resolve } = Promise.withResolvers();

		const rl = readline.createInterface({
			input: fs.createReadStream(filePath),
			crlfDelay: Infinity,
		});

		const deps = [];
		rl.on("line", (line) => {
			const match = /(?<=^\s*#\s*include\s*")[^\s]*(?=")/.exec(line);
			if (match === null) {
				data.content += `${line}\n`;
				return;
			}

			const include = match[0];
			deps.push(
				includeFile(include, getIncludePath(include, filePath)).then(() =>
					included.get(include).adj.push(file)
				)
			);

			data.content += `// ${line}\n`;
		});

		rl.on("close", () =>
			Promise.all(deps)
				.then(() => resolve())
				.catch((err) => reject(err))
		);

		return promise;
	}
	await includeFile("main", progPath);

	// Topological sort
	const seen = new Set();
	const order = [];
	function dfs(a) {
		if (seen.has(a)) return;
		seen.add(a);

		for (const b of included.get(a).adj) {
			dfs(b);
		}
		order.push(a);
	}
	for (const a of included.keys()) {
		dfs(a);
	}
	order.reverse();

	seen.clear();
	for (const a of order) {
		for (const b of included.get(a).adj) {
			if (seen.has(b)) {
				throw new Error("Dependency graph is not acyclic");
			}
		}
	}

	let rv = "";
	for (const a of order) {
		rv += `// beginning of ${quoteForPrint(a)}\n`;
		rv += included.get(a).content;
		rv += `// end of ${quoteForPrint(a)}\n\n`;
	}
	rv = rv.trim();

	return rv;
}

if (esMain(import.meta)) {
	const rv = await expandCCppIncludes(...process.argv.slice(2));
	console.log(rv);
}
