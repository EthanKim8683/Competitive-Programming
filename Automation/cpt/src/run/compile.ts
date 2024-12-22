import cp from "child_process";
import { promisify } from "util";
const exec = promisify(cp.exec);
import { CompilationResult } from "./types";

export default async (args: string[]) =>
	exec(args.join(" "))
		.then(({ stderr }) => ({
			success: true,
			warning: stderr.length > 0 ? stderr : undefined,
		}))
		.catch(({ stderr }) => ({
			success: false,
			error: `could not compile using arguments \`${args.join(" ")}\`:\n${stderr}`,
		})) as Promise<CompilationResult>;
