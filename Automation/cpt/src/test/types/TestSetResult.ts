import TestCaseResult from "./TestCaseResult";

type TestSetResult =
  | {
      success: false;
      errorSymbols: string[];
      reasons: any[];
    }
  | {
      success: true;
      testCaseResults: Record<number, TestCaseResult>;
    };
export default TestSetResult;
