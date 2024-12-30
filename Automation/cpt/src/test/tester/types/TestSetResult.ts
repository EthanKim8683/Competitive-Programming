import TestCaseResult from "./TestCaseResult";

type TestSetResult =
	| {
			success: false;
			errorSymbols: string[];
			reasons: any[];
	  }
	| {
			success: true;
			testCaseResults: TestCaseResult[];
	  };
export default TestSetResult;
