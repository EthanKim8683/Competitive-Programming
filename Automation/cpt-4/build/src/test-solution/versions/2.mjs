import { glob } from "glob";
import path from "path";
import makeRunner from "../../make-runner/make-runner.mjs";
const EXT_TO_LANGUAGE = {
    cpp: "c++20",
    py: "python3",
};
const testSolutionV2 = async (dir) => {
    const [sol] = await glob(path.join(dir, "sol.*"));
    const language = EXT_TO_LANGUAGE[path.extname(sol)];
    const [inputs, outputs] = await Promise.all([
        glob(path.join(dir, "inputs/*.txt")),
        glob(path.join(dir, "outputs/*.txt")),
    ].map((promises) => promises.then((files) => files.sort())));
    const solRunner = await makeRunner(sol, language);
};
export default testSolutionV2;
