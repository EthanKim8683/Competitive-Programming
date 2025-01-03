import { EntryInterface, InitOptions } from "../base";
import cppEntry from "./cpp";

const cpp20Entry: EntryInterface = (filePath: string, options?: InitOptions) =>
	cppEntry(filePath, { ...options, cppOptions: { std: "c++20" } });
export default cpp20Entry;
