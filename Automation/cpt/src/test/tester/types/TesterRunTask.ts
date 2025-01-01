import TesterRunResult from "./TesterRunResult";

type TesterRunTask<T> = (...args: any[]) => {
	promise: Promise<TesterRunResult<T>>;
	kill: () => void;
};
export default TesterRunTask;
