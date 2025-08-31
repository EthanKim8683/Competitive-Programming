import fs from "fs";
import { exec } from "child_process";
import esMain from "es-main";

import {
	inferLanguageUsingFilename,
	quoteForPrint,
	quoteForShell,
} from "./utils.js";

// TODO: Pre-compiled headers
function compileCpp(progPath, exePath, std) {
	const { promise, resolve, reject } = Promise.withResolvers();

	const cmd = [
		"/opt/homebrew/bin/g++-14",
		"-o",
		quoteForShell(exePath),
		quoteForShell(progPath),
		std ? `-std=${std}` : "",
		"-O2",
		"-DETHANKIM8683",
		"-ld_classic", // https://github.com/Homebrew/homebrew-core/issues/145991
		"-I/Users/ethankim8683/Desktop/Competitive-Programming/include",
	].join(" ");

	exec(cmd, (error, _stdout, stderr) => {
		if (error) {
			return reject(
				new Error(`Could not compile using command ${cmd}\nstderr:\n${stderr}`)
			);
		}

		resolve();
	});

	return promise;
}

function compilePython3(progPath, exePath) {
	const { promise, resolve, reject } = Promise.withResolvers();

	const progStream = fs.createReadStream(progPath);
	const exeStream = fs.createWriteStream(exePath);

	exeStream.write("#!/opt/homebrew/bin/pypy\n\n");
	progStream.pipe(exeStream);

	progStream.on("error", (err) =>
		reject(
			new Error(`Error reading from program ${quoteForPrint(progPath)}`, {
				cause: err,
			})
		)
	);

	exeStream.on("close", () =>
		fs.chmod(exePath, 0o777, (err) => {
			if (err) {
				return reject(
					new Error(
						`Error setting permissions for executable ${quoteForPrint(exePath)}`
					)
				);
			}
			resolve();
		})
	);
	exeStream.on("error", (err) =>
		reject(
			new Error(`Error writing to executable ${quoteForPrint(exePath)}`, {
				cause: err,
			})
		)
	);

	return promise;
}

export default function compile(progPath, exePath, lang) {
	lang ??= inferLanguageUsingFilename(progPath);
	switch (lang) {
		case "cpp":
			return compileCpp(progPath, exePath);
		case "cpp17":
			return compileCpp(progPath, exePath, "c++17");
		case "cpp20":
			return compileCpp(progPath, exePath, "c++20");
		case "cpp23":
			return compileCpp(progPath, exePath, "c++23");
		case "python3":
			return compilePython3(progPath, exePath);
		default:
			throw new Error(`Unknown language ${quoteForPrint(lang)}`);
	}
}

if (esMain(import.meta)) {
	const rv = await compile(...process.argv.slice(2));
	console.log(rv);
}
