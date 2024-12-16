export function isScrapedProblemData(scrapedData) {
    return !("problems" in scrapedData);
}
export function isScrapedContestData(scrapedData) {
    return "problems" in scrapedData;
}
