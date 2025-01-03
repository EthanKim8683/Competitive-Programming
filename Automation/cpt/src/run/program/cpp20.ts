import { ProgramInitOptions, ProgramModule } from "../base";
import cpp from "./cpp";

const cpp20: ProgramModule = (
	programPath: string,
	{ cppOptions = {}, ...options }: ProgramInitOptions = {}
) =>
	cpp(programPath, {
		...options,
		cppOptions: { ...cppOptions, std: "c++20" },
	});
export default cpp20;
