type TesterTaskResult<T> =
	| {
			success: false;
			reasons: Record<string, Error | string | (Error | string)[]>;
	  }
	| { success: true; result: T };
export default TesterTaskResult;
