import { gotoWithRetry } from "../../common.mjs";
export default async function fetchCodeforcesProblem(url, name) {
    const page = await gotoWithRetry(url);
    let rv;
    if (await page.$("::-p-xpath(//div[@class='section-title' and contains(text(),'Interaction')])")) {
        rv = {
            name,
            metadata: {
                url,
                platform: "codeforces",
                type: "interactive",
            },
        };
    }
    else {
        const [inputs, outputs] = await Promise.all([
            page.$$eval("div.input pre", (els) => els.map((el) => el.innerText)),
            page.$$eval("div.output pre", (els) => els.map((el) => el.innerText)),
        ]);
        rv = {
            name,
            metadata: {
                url,
                platform: "codeforces",
                type: "batch",
            },
            inputs,
            outputs,
        };
    }
    await page.close();
    return rv;
}
