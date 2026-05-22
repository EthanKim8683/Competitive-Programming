"use strict";

chrome.runtime.onMessage.addListener((message, sender, sendResponse) => {
  sendResponse("Polo!");
  window.close();
});
