type TestCaseResult =
	| {
			passed: false;
			reasons: Record<string, Error | Error[] | string | string[]>;
	  }
	| { passed: true };
export default TestCaseResult;
