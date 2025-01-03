import { EntryInterface, InitOptions } from "../base";
import { CppIniter } from "./cpp";

const cpp20Entry: EntryInterface = (
	filePath: string,
	options?: InitOptions
): CppIniter => new CppIniter(filePath, { ...options, cppStd: "c++20" });
export default cpp20Entry;
