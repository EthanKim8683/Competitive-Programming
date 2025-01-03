import { EntryInterface, InitOptions } from "../base";
import { CppIniter } from "./cpp";

const cpp23Entry: EntryInterface = (
	filePath: string,
	options?: InitOptions
): CppIniter => new CppIniter(filePath, { ...options, cppStd: "c++23" });
export default cpp23Entry;
