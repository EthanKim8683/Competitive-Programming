import cp from "child_process";
import { promisify } from "util";
const exec = promisify(cp.exec);

export default async (args: string[]) =>
  exec(args.join(" "))
    .then(({ stderr }) => (stderr ? { warning: stderr } : {}))
    .catch(({ stderr }) => ({ error: stderr }));
