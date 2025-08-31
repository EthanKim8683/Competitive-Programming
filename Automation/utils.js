import { exec } from "child_process";
import path from "path";
import util from "util";

// TODO: Accept input via stdin
export function runPythonScript(filename, env = {}) {
	const { promise, resolve, reject } = Promise.withResolvers();

	exec(
		"/Users/ethankim8683/Desktop/Competitive-Programming/Automation/.venv/bin/python3 " +
			filename,
		{ env },
		(error, stdout, stderr) => {
			if (error) return reject(error);
			resolve({ stdout, stderr });
		}
	);

	return promise;
}

export function numBytesToString(bytes) {
	for (const [size, unit] of [
		[1e9, "GB"],
		[1e6, "MB"],
		[1e3, "kB"],
	]) {
		if (bytes >= size) {
			return (bytes / size).toFixed(3) + unit;
		}
	}
	return bytes + "B";
}

export function inferLanguageUsingFilename(filename) {
	const match = /(?<=\.)\w+(?=\.\w$)/.exec(filename);
	if (match !== null) {
		return match[0];
	}

	const ext = path.extname(filename);
	switch (ext) {
		case ".cpp":
		case ".hpp":
			return "cpp20";
		case ".py":
			return "python3";
	}

	throw new Error(
		`Could not infer language of file ${quoteForPrint(filename)}`
	);
}

export function quoteForShell(str) {
	return `"${("" + str).replaceAll(/['"`]/g, "\\$&")}"`;
}

export function quoteForPrint(str) {
	return util.inspect("" + str);
}
