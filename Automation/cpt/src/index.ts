import { StdioOption } from "./runner-utils/execute";
import CPPRunner from "./runners/c++";

(async () => {
  const run = await CPPRunner("demo.cpp");
  const { stdout } = await run({ stdin: "2", stdout: StdioOption.STRING });
  process.stdout.write(stdout);
})();
