import { wsconnect } from "@nats-io/nats-core";

let nc;

const onStartupHandler = async () => {
  nc = await wsconnect({ servers: "127.0.0.1:8683" });

  nc.publish("hello-world", "Hello, World!");
};

chrome.runtime.onStartup.addListener(onStartupHandler);
