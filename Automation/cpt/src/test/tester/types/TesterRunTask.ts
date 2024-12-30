import Runner from "../../../run/Runner";

type TesterRunTask = {
	promise: ReturnType<Runner["run"]>;
	runtimeErrorVerdict: string;
};
export default TesterRunTask;
