"use strict";

import { wsconnect } from "@nats-io/nats-core";

// The judges live in the service worker, where they manage tabs and execute
// stuff
//
// The content script just contains tasks the service worker can call
//  - They should expose what tasks can be called
//
// Task instances look like cp.codeforces.problem.1134D.inputs
// Tasks define a regex pattern (`.exec` to get params) and what to do with the
// pattern
//  - If a worker capable of performing the task doesn't exist yet, we parse
//   out the params and open the page as specified by the task
//  - Otherwise, we assign the task to one of the workers
//    - We notify each of the workers, and the first responder is assigned the
//     task
//
// Essentially, for each task, we:
//  1. Announce the task to anyone
//  2. First worker that responds gets the task
//  3. Announce the task to just that worker
//  4. Reply to NATS with the response
//
// In addition to tasks, clicking the extension should trigger an action
//
// An action matches a set of URLs and responds with a command for the CLI
//
// Now, onto implementation details:
//
// When a page is opened, it should add a message event listener which has two
// cases:
//  1. If the message is global, it goes through all the tasks and responds if
//    it can fulfill the tasks in the list which correspond to the message
//  2. If the message is for the current page, it executes the task
//
// For actions, it looks at the tab the action was made on and looks for the
// appropriate action and executes it

chrome.action.onClicked.addListener(async (_tab) => {
  const tabs = await chrome.tabs.query({});
  const response = await Promise.any(
    tabs.map((tab) => chrome.tabs.sendMessage(tab.id, "Marco!"))
  );
  console.log(response);
});

function initNats() {
  wsconnect({});
}

chrome.runtime.onInstalled.addListener(() => {
  initNats();
});

chrome.runtime.onStartup.addListener(() => {
  initNats();
});
