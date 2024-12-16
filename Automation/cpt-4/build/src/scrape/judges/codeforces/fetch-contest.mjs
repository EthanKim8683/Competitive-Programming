import { gotoWithRetry } from "../../common.mjs";
import fetchCodeforcesProblem from "./fetch-problem.mjs";
export default async function fetchCodeforcesContest(url, name) {
    const page = await gotoWithRetry(url);
    const problems = await page
        .$$eval("table.problems tr td:first-child > a", (els) => els.map((el) => [el.textContent.trim(), el.href]))
        .then((problems) => Promise.all(problems.map(([id, url]) => fetchCodeforcesProblem(url, id))));
    await page.close();
    return {
        name,
        problems,
    };
}
