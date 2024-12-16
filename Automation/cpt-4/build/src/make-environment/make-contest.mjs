import makeProblem from "./make-problem.mjs";
import path from "path";
import fs from "fs/promises";
export default async function makeContest(data, dir = process.cwd()) {
    await fs.rm(path.join(dir, data.name), { recursive: true }).catch(() => { });
    await fs.mkdir(path.join(dir, data.name), { recursive: true });
    await Promise.all(data.problems.map((problemData) => makeProblem(problemData, path.join(dir, data.name))));
}
