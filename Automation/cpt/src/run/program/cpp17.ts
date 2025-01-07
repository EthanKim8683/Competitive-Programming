import { ProgramModule } from "./base";
import cpp from "./cpp";

const cpp17: ProgramModule = (programPath: string) =>
	cpp(programPath, { std: "c++17" });
export default cpp17;
