import TesterTaskResult from "./TesterTaskResult";

type TesterRunTask<T> = (...args: any[]) => {
	promise: Promise<TesterTaskResult<T>>;
	kill: () => void;
};
export default TesterRunTask;
