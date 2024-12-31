import TestSetResult from "../../types/TestSetResult";
import TestCaseResult from "../../types/TestCaseResult";

export default async (
  keys: number[],
  test: (key: number) => Promise<TestCaseResult>
): Promise<TestSetResult> =>
  Promise.all(keys.map((key) => test(key))).then((testCaseResults) => ({
    success: true,
    testCaseResults: Object.fromEntries(
      testCaseResults.map((testCaseResult, index) => [
        keys[index],
        testCaseResult,
      ])
    ),
  }));
