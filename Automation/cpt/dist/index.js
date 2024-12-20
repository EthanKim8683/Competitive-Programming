import compile from "./runner-utils/compile";
import execute from "./runner-utils/execute";
import fs from "fs";
await compile(["/opt/homebrew/bin/g++-14", "-o", "o", "demo.cpp"]);
console.log(JSON.stringify(await execute(["./o"], {
    stdin: fs.openSync("in.txt", "r"),
    stdout: fs.openSync("out.txt", "w"),
})));
