type TesterInitTaskErrorHandler = (
	error: Error,
	initErrorSymbol: string
) => string | undefined;
export default TesterInitTaskErrorHandler;
