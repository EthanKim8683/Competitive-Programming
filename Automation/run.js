import { spawn } from "child_process";
import path from "path";
import fs from "fs";
import tmp from "tmp";
import esMain from "es-main";

export default function run(exePath, callback = () => {}) {
	const { promise, resolve, reject } = Promise.withResolvers();

	if (!path.isAbsolute(exePath)) {
		exePath = path.join(process.cwd(), exePath);
	}

	tmp.file((err, logPath, _fd, clean) => {
		if (err)
			return reject(new Error("Error while creating logfile", { cause: err }));

		const child = spawn("/usr/bin/time", ["-o", logPath, "-l", exePath]);
		callback(child.stdin, child.stdout, child.stderr);

		child.on("error", (err) => reject(err));
		child.on("close", () => {
			fs.readFile(logPath, (err, data) => {
				if (err) {
					clean();
					return reject(
						new Error("Error while reading logfile", { cause: err })
					);
				}

				data = data.toString();
				const user = /\d+\.\d+(?= user)/.exec(data)?.[0];
				const sys = /\d+\.\d+(?= sys)/.exec(data)?.[0];
				const maxrss = /\d+(?=  maximum resident set size)/.exec(data)?.[0];
				if (!user || !sys || !maxrss) {
					return reject(
						new Error(`Could not parse /usr/bin/time output\noutput:\n${data}`)
					);
				}

				const time = parseFloat(user) + parseFloat(sys);
				const memory = parseInt(maxrss);

				clean();
				resolve({ time, memory });
			});
		});
	});

	return promise;
}

if (esMain(import.meta)) {
	const rv = await run(...process.argv.slice(2));
	console.log(rv);
}
