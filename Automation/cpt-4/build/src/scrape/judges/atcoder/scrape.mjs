import fetchAtCoderProblem from "./fetch-problem.mjs";
import fetchAtCoderContest from "./fetch-contest.mjs";
import submitAtCoder from "./submit-solution.mjs";
const atCoderScraper = {
    tryFetch: (url) => {
        let exec;
        if ((exec = /atcoder\.jp\/contests\/.+\/tasks\/([^/?]+)$/.exec(url))) {
            return fetchAtCoderProblem(url, exec[1]);
        }
        else if ((exec = /atcoder\.jp\/contests\/([^/?]+)$/.exec(url))) {
            return fetchAtCoderContest(url, exec[1]);
        }
    },
    trySubmit: (url, sol) => {
        let exec;
        if ((exec = /atcoder\.jp\/contests\/.+\/tasks\/([^/?]+)$/.exec(url))) {
            return submitAtCoder(url, sol);
        }
    },
};
export default atCoderScraper;
