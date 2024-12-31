import Runner from "../../../run/Runner";

type TesterRunTask = {
	promise: ReturnType<Runner["run"]>;
	runtimeErrorVerdictSymbol: string;
};
export default TesterRunTask;
