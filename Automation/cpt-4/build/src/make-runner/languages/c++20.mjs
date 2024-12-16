import { exec } from "child_process";
import path from "path";
import fs from "fs";
const makeCppRunner = async (code) => {
    const { dir, name } = path.parse(code);
    const binary = path.join(dir, name);
    await new Promise((resolve, reject) => {
        exec([
            process.env.GCC_PATH,
            "-O2",
            "-std=c++20",
            "-DETHANKIM8683",
            "-I/Users/ethankim8683/Desktop/Competitive-Programming/include",
            code,
            "-o",
            binary,
        ].join(" "), (err) => {
            if (err)
                return reject(err);
            resolve();
        });
    });
    process.on("exit", () => {
        fs.rmSync(binary);
    });
    return (...args) => new Promise((resolve, reject) => exec([binary, ...args].join(" "), (err, stdout, stderr) => {
        if (err)
            return reject(err);
        resolve({ stdout, stderr });
    }));
};
export default makeCppRunner;
