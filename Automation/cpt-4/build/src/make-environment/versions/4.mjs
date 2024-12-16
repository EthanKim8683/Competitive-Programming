import fs from "fs/promises";
import path from "path";
import INI from "ini";
import config from "../../config.json" with { type: "json" };
const __dirname = import.meta.dirname;
const makeProblemV4 = async (data, dir) => {
    await fs.rm(path.join(dir, data.name), { recursive: true }).catch(() => { });
    await fs.mkdir(path.join(dir, data.name), { recursive: true });
    const { ext } = config.languageInfo[data.metadata.language];
    const promises = [
        (async () => {
            const solPath = path.join(dir, data.name, `sol.${ext}`);
            fs.copyFile(path.join(__dirname, `../../../../templates/${data.metadata.type}.${ext}`), solPath).catch(() => fs.writeFile(solPath, ""));
        })(),
        fs.writeFile(path.join(dir, data.name, ".metadata.ini"), INI.stringify(data.metadata)),
    ];
    if (data.metadata.type == "batch") {
        data = data;
        promises.push((async () => {
            const inputsPath = path.join(dir, data.name, "inputs");
            await fs.mkdir(inputsPath, { recursive: true });
            await Promise.all(data.inputs.map((input, index) => fs.writeFile(path.join(inputsPath, `${index + 1}.txt`), input)));
        })(), (async () => {
            const outputsPath = path.join(dir, data.name, "outputs");
            await fs.mkdir(outputsPath, { recursive: true });
            await Promise.all(data.outputs.map((input, index) => fs.writeFile(path.join(outputsPath, `${index + 1}.txt`), input)));
        })());
    }
    await Promise.all(promises);
};
export default makeProblemV4;
