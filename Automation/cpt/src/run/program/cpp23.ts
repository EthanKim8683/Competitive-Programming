import { ProgramInitOptions, ProgramModule } from "./base";
import cpp from "./cpp";

const cpp23: ProgramModule = (
	programPath: string,
	{ cppOptions = {}, ...options }: ProgramInitOptions = {}
) =>
	cpp(programPath, {
		...options,
		cppOptions: { ...cppOptions, std: "c++23" },
	});
export default cpp23;
