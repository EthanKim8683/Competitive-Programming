import { glob } from "glob";
import path from "path";
import { error } from "../common.mjs";
import config from "../config.json" with { type: "json" };
const __dirname = import.meta.dirname;
const makers = await glob(path.join(__dirname, "versions/*.mjs"))
    .then((makerPaths) => Promise.all(makerPaths.map((makerPath) => import(makerPath).then((module) => [
    path.parse(makerPath).name,
    module.default,
]))))
    .then((makerEntries) => Object.fromEntries(makerEntries));
export default function makeProblem(data, dir = process.cwd()) {
    data.metadata.version ??= config.defaultVersion;
    data.metadata.language ??= config.defaultLanguage;
    if (!(data.metadata.version in makers)) {
        error(`Unknown CPT version '${data.metadata.version}'`);
    }
    return makers[data.metadata.version](data, dir);
}
