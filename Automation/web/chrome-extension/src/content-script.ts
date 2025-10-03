"use strict";

chrome.runtime.onMessage.addListener((message, sender, sendResponse) => {
  sendResponse(`Polo! (${window.location.href})`);
});
