import compile from "../runner-utils/compile";
import execute from "../runner-utils/execute";
import tmp from "tmp-promise";
import path from "path";
export default async (codePath) => {
    const { path: exePath } = await tmp.file();
    await compile(["/opt/homebrew/bin/g++-14", "-o", exePath, codePath]);
    return async (stdio) => execute([path.relative(process.cwd(), exePath)], stdio);
};
