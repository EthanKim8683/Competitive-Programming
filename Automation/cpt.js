import fs from "fs";
import path from "path";
import { program } from "commander";
import clipboard from "clipboardy";
import "colors";

import compile from "./compile.js";
import compileWithCache from "./compile_with_cache.js";
import expandCCppIncludes from "./expand_c_cpp_includes.js";
import run from "./run.js";
import runUsingInputs from "./run_using_inputs.js";
import {
	inferLanguageUsingFilename,
	numBytesToString,
	runPythonScript,
} from "./utils.js";

const __dirname = import.meta.dirname;

async function cliCompile(progPath, exePath, { lang, force }) {
	return exePath
		? compile(progPath, exePath, lang)
		: compileWithCache(progPath, lang, force);
}

async function cliRun(exePath, { inputs, series }) {
	if (inputs) {
		const results = await runUsingInputs(exePath, inputs, series);

		for (let i = 0; i < results.length; i++) {
			const { rusage, output } = results[i];
			const { time, memory } = rusage;
			const adjustedMemory = memory - 9994240;

			let log =
				(
					"-".repeat(40) +
					` CASE ${i + 1} ---- ` +
					`${time}s, ` +
					`${numBytesToString(adjustedMemory)} ` +
					`(${numBytesToString(memory)} raw) ` +
					"-".repeat(40)
				).bold + "\n\n";
			for (const { from, data } of output) {
				if (from === "stdout") {
					log += data;
				} else {
					const trimmed = data.trimEnd();
					const ws = data.substr(trimmed.length);
					log += trimmed.blue + ws;
				}
			}
			log = log.trimEnd() + "\n";
			console.log(log);
		}
	} else {
		const { time, memory } = await run(exePath, (stdin, stdout, stderr) => {
			process.stdin.pipe(stdin);
			stdout.pipe(process.stdout);
			stderr.pipe(process.stderr);
		});
		const adjustedMemory = memory - 10354688;
		console.log(
			(
				`\n${time}s ` +
				`${numBytesToString(adjustedMemory)} ` +
				`(${numBytesToString(memory)} raw)`
			).bold
		);
	}
}

program.version("0.0.1");

program
	.command("compile <progPath> [exePath]")
	.description("compiles program, caching if exePath is omitted")
	.option("-l, --lang <lang>", "Language program should be compiled with")
	.option("-f", "--force", "Force recompilation if compiling with cache")
	.action((...args) => cliCompile(...args).then(console.log));

program
	.command("copy <progPath>")
	.description("copies standalone version of program onto clipboard")
	.option(
		"-l, --lang <lang>",
		"Language of program; used to expand dependencies"
	)
	.action((progPath, { lang }) => {
		lang ??= inferLanguageUsingFilename(progPath);

		if (/cpp\d+/.test(lang)) {
			expandCCppIncludes(progPath).then((code) => clipboard.writeSync(code));
		} else {
			clipboard.writeSync(fs.readFileSync(progPath));
		}
	});

program
	.command("run <exePath>")
	.description("runs executable")
	.option("-i, --inputs <dir>", "Directory of inputs to run with")
	.option("-s, --series", "Run inputs in series (default is parallel)")
	.action(cliRun);

program
	.command("compile-and-run <progPath> [exePath]")
	.alias("cnr")
	.description("compiles and runs program")
	.option("-l, --lang <lang>", "Language program should be compiled with")
	.option("-i, --inputs <dir>", "Directory of inputs to run with")
	.option("-s, --series", "Run inputs in series (default is parallel)")
	.action(async (progPath, exePath, { lang, inputs }) => {
		const exePath2 = await cliCompile(progPath, exePath, { lang });
		exePath ??= exePath2;
		await cliRun(exePath, { inputs });
	});

program
	.command("plot")
	.description("plot data provided via stdin")
	.option("-t, --type <scatter>", "Type of plot")
	.action(({ type = "scatter" }) => {
		switch (type) {
			case "scatter":
				runPythonScript(path.join(__dirname, "scatter_plot.py"));
				break;
			default:
				throw new Error(`Unknown plot type: ${type}`);
		}
	});

program.parse(process.argv);
