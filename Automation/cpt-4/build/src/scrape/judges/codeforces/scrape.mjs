import fetchCodeforcesProblem from "./fetch-problem.mjs";
import fetchCodeforcesContest from "./fetch-contest.mjs";
import submitCodeforces from "./submit.mjs";
const codeforcesScraper = {
    tryFetch: (url) => {
        let exec;
        if ((exec = /codeforces\.com\/contest\/([^/?]+)\/problem\/([^/?]+)$/.exec(url)) ||
            (exec = /codeforces\.com\/problemset\/problem\/([^/?]+)\/([^/?]+)$/.exec(url))) {
            return fetchCodeforcesProblem(url, exec[1] + exec[2]);
        }
        else if ((exec = /codeforces\.com\/contest\/([^/?]+)$/.exec(url))) {
            return fetchCodeforcesContest(url, exec[1]);
        }
    },
    trySubmit: (url, sol) => {
        let exec;
        if ((exec = /codeforces\.com\/contest\/([^/?]+)\/problem\/([^/?]+)$/.exec(url)) ||
            (exec = /codeforces\.com\/problemset\/problem\/([^/?]+)\/([^/?]+)$/.exec(url))) {
            return submitCodeforces(url, sol);
        }
    },
};
export default codeforcesScraper;
