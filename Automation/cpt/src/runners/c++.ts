import compile from "../runner-utils/compile";
import { partial } from "../runner-utils/execute";
import tmp from "tmp-promise";
import path from "path";

export default async (codePath: string) => {
  const { path: exePath } = await tmp.file();

  await compile([
    "/opt/homebrew/bin/g++-14",
    "-o",
    exePath,
    codePath,
    "-O2",
    "-DETHANKIM8683",
  ]);

  return partial([path.relative(process.cwd(), exePath)]);
};
