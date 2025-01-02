import { RunnerOptions } from "../base";
import CppRunner from "./cpp";

export default class Cpp20Runner extends CppRunner {
	constructor(filePath: string, options?: RunnerOptions) {
		super(filePath, { ...options, cppStd: "c++20" });
	}
}
