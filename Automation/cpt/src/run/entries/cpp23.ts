import { EntryInterface, InitOptions } from "../base";
import cppEntry from "./cpp";

const cpp23Entry: EntryInterface = (filePath: string, options?: InitOptions) =>
	cppEntry(filePath, { ...options, cppOptions: { std: "c++23" } });
export default cpp23Entry;
