import TesterInitTaskErrorHandler from "./TesterInitTaskErrorHandler";

type TesterInitTask<T> = {
	promise: Promise<T>;
	initErrorSymbol: string;
	errorHandlers?: TesterInitTaskErrorHandler[];
};
export default TesterInitTask;
