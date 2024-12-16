import { glob } from "glob";
import path from "path";
import fs from "fs/promises";
import INI from "ini";
const __dirname = import.meta.dirname;
const testers = await glob(path.join(__dirname, "versions/*.mjs"))
    .then((testerPaths) => Promise.all(testerPaths.map((testerPath) => import(testerPath).then((module) => [
    path.parse(testerPath).name,
    module.default,
]))))
    .then((makerEntries) => Object.fromEntries(makerEntries));
export default async function testSolution(dir) {
    let version;
    try {
        const metadata = INI.parse(await fs
            .readFile(path.join(dir, ".metadata.ini"))
            .then((buf) => buf.toString()));
        version = metadata.version;
    }
    catch (e) {
        version = "2";
    }
    return testers[version](dir);
}
