import { EntryInterface, InitOptions } from "../base";
import cppEntry from "./cpp";

const cpp17Entry: EntryInterface = (filePath: string, options?: InitOptions) =>
	cppEntry(filePath, { ...options, cppOptions: { std: "c++17" } });
export default cpp17Entry;
