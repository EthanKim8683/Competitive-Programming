import { EntryInterface } from "./base";
import cppEntry from "./entries/cpp";
import cpp17Entry from "./entries/cpp17";
import cpp20Entry from "./entries/cpp20";
import cpp23Entry from "./entries/cpp23";
import dirEntry from "./entries/dir";
import python3Entry from "./entries/python3";

const entries: Record<string, EntryInterface> = {
	cpp: cppEntry,
	cpp17: cpp17Entry,
	cpp20: cpp20Entry,
	cpp23: cpp23Entry,
	dir: dirEntry,
	python3: python3Entry,
};
export default entries;
