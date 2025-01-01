import TestCaseResult from "./TestCaseResult";

type TestSetResult =
	| {
			success: false;
			reasons: Record<string, Error | string | (Error | string)[]>;
	  }
	| {
			success: true;
			testCaseResults: Record<number, TestCaseResult>;
	  };
export default TestSetResult;
