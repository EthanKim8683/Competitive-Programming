type TestCaseResult =
	| {
			passed: false;
			reasons: Record<string, Error | string | (Error | string)[]>;
	  }
	| { passed: true };
export default TestCaseResult;
