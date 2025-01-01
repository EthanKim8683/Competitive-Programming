import TesterTaskResult from "./TesterTaskResult";

type TesterInitTask<T> = (...args: any[]) => Promise<TesterTaskResult<T>>;
export default TesterInitTask;
