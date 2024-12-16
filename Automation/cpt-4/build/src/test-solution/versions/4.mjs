import { glob } from "glob";
import path from "path";
import INI from "ini";
import makeRunner from "../../make-runner/make-runner.mjs";
import fs from "fs/promises";
const testSolutionV4 = async (dir) => {
    const metadata = INI.parse(await fs
        .readFile(path.join(dir, ".metadata.ini"))
        .then((buf) => buf.toString()));
    const [sol] = await glob(path.join(dir, "sol.*"));
    const { stdout, stderr } = await makeRunner(sol, metadata.language).then((runner) => runner());
    console.log(stdout);
};
export default testSolutionV4;
