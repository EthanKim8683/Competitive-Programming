"use strict";

function waitForTabComplete(
  tabId: number,
  { timeout = 10_000 }: { timeout?: number } = {},
) {
  const { promise, resolve, reject } = Promise.withResolvers<void>();

  const listener = (id: number, info: chrome.tabs.OnUpdatedInfo) => {
    if (id !== tabId) return;
    if (info.status !== "complete") return;
    chrome.tabs.onUpdated.removeListener(listener);
    resolve();
  };

  setTimeout(() => {
    chrome.tabs.onUpdated.removeListener(listener);
    reject(new Error(`waitForTabComplete timed out after ${timeout}ms`));
  }, timeout);
  chrome.tabs.onUpdated.addListener(listener);

  return promise;
}

chrome.action.onClicked.addListener(async (_tab) => {
  const tab = await chrome.tabs.create({
    url: "https://google.com",
    pinned: true,
    active: false,
  });

  await waitForTabComplete(tab.id);
  const response = await chrome.tabs.sendMessage(tab.id, "Marco!");
  console.log(response);
});
