import TesterInitResult from "./TesterInitResult";

type TesterInitTask<T> = (...args: any[]) => Promise<TesterInitResult<T>>;
export default TesterInitTask;
