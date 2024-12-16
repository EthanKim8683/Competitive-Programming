import { gotoWithRetry } from "../../common.mjs";
export default async function fetchAtCoderProblem(url, name) {
    const page = await gotoWithRetry(url);
    let rv;
    if (await page.$("::-p-xpath(//h3[starts-with(text(),'Sample Output')])")) {
        const [inputs, outputs] = await Promise.all([
            page.$$eval("::-p-xpath(//section[h3[starts-with(text(),'Sample Input')]]/pre)", (els) => els.map((el) => el.innerText)),
            page.$$eval("::-p-xpath(//section[h3[starts-with(text(),'Sample Output')]]/pre)", (els) => els.map((el) => el.innerText)),
        ]);
        rv = {
            name,
            metadata: {
                url,
                platform: "atcoder",
                type: "batch",
            },
            inputs,
            outputs,
        };
    }
    else {
        rv = {
            name,
            metadata: {
                url,
                platform: "atcoder",
                type: "interactive",
            },
        };
    }
    await page.close();
    return rv;
}
