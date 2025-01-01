type TesterInitResult<T> =
	| {
			success: false;
			reasons: Record<string, Error | Error[]>;
	  }
	| { success: true; result: T };
export default TesterInitResult;
