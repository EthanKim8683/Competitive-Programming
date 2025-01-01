import TestCaseResult from "./TestCaseResult";

type TestSetResult =
	| {
			success: false;
			reasons: Record<string, Error | Error[]>;
	  }
	| {
			success: true;
			testCaseResults: Record<number, TestCaseResult>;
	  };
export default TestSetResult;
