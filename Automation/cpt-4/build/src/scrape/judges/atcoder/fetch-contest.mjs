import { gotoWithRetry } from "../../common.mjs";
import fetchAtCoderProblem from "./fetch-problem.mjs";
export default async function fetchAtCoderContest(url, name) {
    const page = await gotoWithRetry(`${url}/tasks`);
    const problems = await page
        .$$eval("table tr td:first-child > a", (els) => els.map((el) => [el.textContent.trim(), el.href]))
        .then((problems) => Promise.all(problems.map(([id, url]) => fetchAtCoderProblem(url, id))));
    await page.close();
    return {
        name,
        problems,
    };
}
