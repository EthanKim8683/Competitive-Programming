import { EntryInterface, InitOptions } from "../base";
import { CppIniter } from "./cpp";

const cpp17Entry: EntryInterface = (
	filePath: string,
	options?: InitOptions
): CppIniter => new CppIniter(filePath, { ...options, cppStd: "c++17" });
export default cpp17Entry;
