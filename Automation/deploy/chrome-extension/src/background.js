"use strict";

import { wsconnect } from "@nats-io/nats-core";

// With background scripts you can communicate with popup
// and contentScript files.
// For more information on background script,
// See https://developer.chrome.com/extensions/background_pages

let nc;
chrome.runtime.onMessage.addListener((request, sender, sendResponse) => {
  if (request.type === "GREETINGS") {
    const responseMessage = `Hi ${
      sender.tab ? "Con" : "Pop"
    }, my name is Bac. I am from Background. It's great to hear from you.`;

    const requestMessage = request.payload.message;
    (async () => {
      if (!nc) {
        nc = await wsconnect({ servers: "ws://127.0.0.1:8684" });
      }
      nc.publish("cp.test", requestMessage);
    })();

    // Log message coming from the `request` parameter
    console.log(requestMessage);
    // Send a response message
    sendResponse({
      message: responseMessage,
    });
  }
});
