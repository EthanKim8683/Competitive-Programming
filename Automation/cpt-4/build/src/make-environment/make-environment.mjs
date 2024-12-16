import makeProblem from "./make-problem.mjs";
import makeContest from "./make-contest.mjs";
import { isScrapedProblemData } from "../types.mjs";
export default async function makeEnvironement(data, dir = process.cwd()) {
    if (isScrapedProblemData(data)) {
        await makeProblem(data, dir);
    }
    else {
        await makeContest(data, dir);
    }
}
