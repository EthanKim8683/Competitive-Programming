import { execSync } from "child_process";

export default (args: string[]): string | undefined => {
	return (
		execSync(
			// Basic sanitization for personal use. Just making sure I don't
			// accidentally hack myself.
			args.map((arg) => `"${arg.replaceAll(/[`"]/g, "\\$&")}"`).join(" "),
			{ stdio: "pipe" }
		).toString() || undefined
	);
};
