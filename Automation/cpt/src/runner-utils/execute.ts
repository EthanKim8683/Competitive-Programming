import { spawn } from "child_process";
import tmp from "tmp";
import fs from "fs/promises";
import { Readable, Writable } from "stream";

export enum StdioOption {
  STRING,
  INHERIT,
  IGNORE,
}

function stdioOptionToSpawnStdioOption(stdioOption: StdioOption) {
  switch (stdioOption) {
    case StdioOption.STRING:
      return "pipe";
    case StdioOption.INHERIT:
      return "inherit";
    case StdioOption.IGNORE:
      return "ignore";
  }
}

// Default values for union type arguments:
// https://stackoverflow.com/a/58599153/19662543

type StdinOptionType = string | StdioOption.INHERIT | ReadableStream;
type StdoutOptionType = StdioOption | Writable;
type StderrOptionType = StdioOption | Writable;

type StdioOptionsType<
  T0 extends StdinOptionType | undefined,
  T1 extends StdoutOptionType | undefined,
  T2 extends StderrOptionType | undefined
> = {
  stdin?: T0;
  stdout?: T1;
  stderr?: T2;
};

type ReturnValueType<
  T1 extends StdoutOptionType,
  T2 extends StderrOptionType
> = Promise<{
  code: number | null;
  signal: NodeJS.Signals | null;
  stdout: T1 extends StdioOption.STRING ? string : null;
  stderr: T2 extends StdioOption.STRING ? string : null;
  maxrss: number;
  cpu: number;
}>;

function execute<
  T0 extends StdinOptionType = StdioOption.INHERIT,
  T1 extends StdoutOptionType = StdioOption.INHERIT,
  T2 extends StderrOptionType = StdioOption.INHERIT
>(
  args: string[],
  stdioOptions?: StdioOptionsType<T0, T1, T2>
): ReturnValueType<T1, T2>;

function execute(
  args: string[]
): ReturnValueType<StdioOption.STRING, StdioOption.STRING>;

function execute(
  args: string[],
  {
    stdin: stdinOption = StdioOption.INHERIT,
    stdout: stdoutOption = StdioOption.INHERIT,
    stderr: stderrOption = StdioOption.INHERIT,
  }: StdioOptionsType<
    StdinOptionType | undefined,
    StdoutOptionType | undefined,
    StderrOptionType | undefined
  > = {}
) {
  return new Promise((resolve, reject) => {
    tmp.file((err, rusagePath) => {
      if (err) return reject(err);

      const child = spawn("/usr/bin/time", ["-l", "-o", rusagePath, ...args], {
        stdio: [
          typeof stdinOption === "string" || stdinOption instanceof Readable
            ? "pipe"
            : "inherit",
          stdoutOption === StdioOption.STRING ||
          stdoutOption instanceof Writable
            ? "pipe"
            : stdioOptionToSpawnStdioOption(stdoutOption),
          stderrOption === StdioOption.STRING ||
          stderrOption instanceof Writable
            ? "pipe"
            : stdioOptionToSpawnStdioOption(stderrOption),
        ],
      });

      {
        if (typeof stdinOption === "string")
          child.stdin!.write(`${stdinOption}\n`);

        if (stdinOption instanceof Readable) stdinOption.pipe(child.stdin!);
      }

      let stdout = "";
      {
        if (stdoutOption === StdioOption.STRING)
          child.stdout!.on("data", (data) => (stdout += data));

        if (stdoutOption instanceof Writable) child.stdout!.pipe(stdoutOption);
      }

      let stderr = "";
      {
        if (stderrOption === StdioOption.STRING)
          child.stderr!.on("data", (data) => (stderr += data));

        if (stderrOption instanceof Writable) child.stderr!.pipe(stderrOption);
      }

      child.on("error", (err) => reject(`process had an error:\n${err}`));

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
          stdout: stdoutOption === StdioOption.STRING ? stdout : null,
          stderr: stderrOption === StdioOption.STRING ? stderr : null,
          maxrss: parseInt(maxrssMatch[0]),
          cpu: parseFloat(userMatch[0]) + parseFloat(sysMatch[0]),
        });
      });
    });
  });
}

export default execute;

export function partial(args: string[]) {
  return <
    T0 extends StdinOptionType,
    T1 extends StdoutOptionType,
    T2 extends StderrOptionType
  >(stdio?: {
    stdin?: T0;
    stdout?: T1;
    stderr?: T2;
  }) => execute<T0, T1, T2>(args, stdio);
}
