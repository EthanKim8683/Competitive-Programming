import TestCaseResult from "./TestCaseResult";

type TestSetResult =
	| {
			success: false;
			errorSymbols: string[];
	  }
	| {
			success: true;
			testCaseResults: TestCaseResult[];
	  };
export default TestSetResult;
