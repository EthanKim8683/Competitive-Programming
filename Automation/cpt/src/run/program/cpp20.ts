import { ProgramModule } from "./base";
import cpp from "./cpp";

const cpp20: ProgramModule = (programPath: string) =>
	cpp(programPath, { std: "c++20" });
export default cpp20;
