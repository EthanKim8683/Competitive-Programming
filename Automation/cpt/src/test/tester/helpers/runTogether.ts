import RunnerRuntimeError from "../../../run/types/RunnerRuntimeError";
import TesterRunTask from "../types/TesterRunTask";
import TestCaseResult from "../types/TestCaseResult";

export default (tasks: TesterRunTask[]): Promise<TestCaseResult | undefined> =>
	Promise.all(tasks.map((task) => task.promise))
		.then(() => undefined)
		.catch((err) => {
			if (err instanceof RunnerRuntimeError)
				return {
					passed: false,
					verdict: tasks.find((task) => task.promise === err.runPromise)!
						.runtimeErrorVerdict,
				};

			throw new Error("Unhandled error", { cause: err });
		});
