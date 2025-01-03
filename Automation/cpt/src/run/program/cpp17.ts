import { ProgramInitOptions, ProgramModule } from "../base";
import cpp from "./cpp";

const cpp17: ProgramModule = (
	programPath: string,
	{ cppOptions = {}, ...options }: ProgramInitOptions = {}
) =>
	cpp(programPath, {
		...options,
		cppOptions: { ...cppOptions, std: "c++17" },
	});
export default cpp17;
