import { ProgramModule } from "./base";
import cpp from "./cpp";

const cpp23: ProgramModule = (programPath: string) =>
	cpp(programPath, { std: "c++23" });
export default cpp23;
