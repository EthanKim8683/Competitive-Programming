import cp from "child_process";
import { promisify } from "util";
const exec = promisify(cp.exec);

export default async (args: string[]) =>
	exec(args.map((arg) => `"${arg}"`).join(" "))
		.then(({ stderr }) => ({
			success: true,
			warning: stderr.length > 0 ? stderr : undefined,
		}))
		.catch(({ stderr }) => ({
			success: false,
			error: stderr,
		})) as Promise<
		{ success: true; warning?: string } | { success: false; error: string }
	>;
