import { connect } from "puppeteer-real-browser";
import { error } from "../common.mjs";
let browser;
export async function gotoWithRetry(url, defaultRetryAfter = 500) {
    if (!browser) {
        ({ browser } = await connect({ headless: false, turnstile: true }));
        process.on("exit", () => {
            browser.close();
        });
    }
    const page = await browser.newPage();
    await page.setRequestInterception(true);
    let ignore403 = false;
    page.on("request", (req) => {
        if (req.url().startsWith("https://challenges.cloudflare.com")) {
            ignore403 = true;
        }
        req.continue();
    });
    await (async function retry() {
        const res = await page.goto(url, { waitUntil: "networkidle0" });
        if (!res)
            return;
        if (res.status() == 429) {
            let retryAfter = defaultRetryAfter;
            if ("retry-after" in res.headers()) {
                retryAfter = parseInt(res.headers()["retry-after"]);
            }
            await new Promise((resolve) => setTimeout(resolve, retryAfter));
            return retry();
        }
        else if (res.status() == 403 && ignore403) {
            await page.waitForNetworkIdle({ concurrency: 1 });
        }
        else if (res.status() >= 400 && res.status() <= 599) {
            error(`Failed to open '${url}' with status code ${res.status()}`);
        }
    })();
    return page;
}
