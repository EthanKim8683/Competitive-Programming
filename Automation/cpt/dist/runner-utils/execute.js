import { spawn } from "child_process";
import tmp from "tmp-promise";
import fs from "fs/promises";
export var StdioOption;
(function (StdioOption) {
    StdioOption[StdioOption["PIPE"] = 0] = "PIPE";
    StdioOption[StdioOption["INHERIT"] = 1] = "INHERIT";
    StdioOption[StdioOption["IGNORE"] = 2] = "IGNORE";
})(StdioOption || (StdioOption = {}));
function stdioOptionToSpawnStdioOption(stdioOption) {
    switch (stdioOption) {
        case StdioOption.PIPE:
            return "pipe";
        case StdioOption.INHERIT:
            return "inherit";
        case StdioOption.IGNORE:
            return "ignore";
    }
}
export default async (args, { stdin = "", stdout: stdoutOption = StdioOption.PIPE, stderr: stderrOption = StdioOption.PIPE, } = {}) => {
    const { path: rusagePath } = await tmp.file();
    return new Promise((resolve, reject) => {
        const child = spawn("/usr/bin/time", ["-l", "-o", rusagePath, ...args], {
            stdio: [
                typeof stdin === "string" ? "pipe" : "inherit",
                stdioOptionToSpawnStdioOption(stdoutOption),
                stdioOptionToSpawnStdioOption(stderrOption),
            ],
        });
        if (typeof stdin === "string") {
            child.stdin.write(stdin);
        }
        let stdout;
        if (stdoutOption === StdioOption.PIPE) {
            stdout = "";
            child.stdout.on("data", (data) => (stdout += data));
        }
        let stderr;
        if (stdoutOption === StdioOption.PIPE) {
            stderr = "";
            child.stderr.on("data", (data) => (stderr += data));
        }
        child.on("error", (err) => {
            reject(`process had an error:\n${err}`);
        });
        child.on("close", async (code, signal) => {
            const rusage = await fs
                .readFile(rusagePath)
                .then((buffer) => buffer.toString());
            const maxrssMatch = /\d+(?=\s+maximum resident set size)/.exec(rusage);
            const userMatch = /\d+\.\d+(?=\s+user)/.exec(rusage);
            const sysMatch = /\d+\.\d+(?=\s+sys)/.exec(rusage);
            if (!maxrssMatch || !userMatch || !sysMatch)
                return reject("could not parse rusage");
            resolve({
                code,
                signal,
                stdout,
                stderr,
                maxrss: parseInt(maxrssMatch[0]),
                cpu: parseFloat(userMatch[0]) + parseFloat(sysMatch[0]),
            });
        });
    });
};
