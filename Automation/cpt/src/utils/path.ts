import os from "os";
import path from "path";

// Works for zsh
export function absolute(pathString: string): string {
	if (pathString.length < 1) return pathString;

	if (pathString[0] === "~") return os.homedir() + pathString.slice(1);
	if (pathString[0] === "/") return pathString;
	return path.join(process.cwd(), pathString);
}
