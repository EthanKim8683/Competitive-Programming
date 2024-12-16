import { glob } from "glob";
import path from "path";
import { error } from "../common.mjs";
const __dirname = import.meta.dirname;
const scrapers = await glob(path.join(__dirname, "judges/*/scrape.mjs")).then((scraperPaths) => Promise.all(scraperPaths.map((scraperPath) => import(scraperPath).then((module) => module.default))));
export function fetch(url) {
    const rv = scrapers.reduce((accum, scraper) => accum ?? scraper.tryFetch(url), undefined);
    if (!rv)
        error(`Could not determine judge from '${url}'`);
    return rv;
}
export function submit(url, sol) {
    const rv = scrapers.reduce((accum, scraper) => accum ?? scraper.trySubmit(url, sol), undefined);
    if (!rv)
        error(`Could not determine judge from '${url}'`);
    return rv;
}
