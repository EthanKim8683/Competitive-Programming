import TestCaseResult from "./TestCaseResult";

type TestSetResult =
	| {
			success: false;
			reasons: Record<string, Error | string | (Error | string)[]>;
	  }
	| {
			success: true;
			results: Record<number, TestCaseResult>;
	  };
export default TestSetResult;
