import { glob } from "glob";
import path from "path";
import { error } from "../common.mjs";
const __dirname = import.meta.dirname;
const makers = await glob(path.join(__dirname, "languages/*.mjs"))
    .then((makerPaths) => Promise.all(makerPaths.map((makerPath) => import(makerPath).then((module) => [
    path.parse(makerPath).name,
    module.default,
]))))
    .then((runnerEntries) => Object.fromEntries(runnerEntries));
export default function makeRunner(code, language) {
    if (!(language in makers)) {
        error(`Unknown solution language '${language}'`);
    }
    return makers[language](code);
}
