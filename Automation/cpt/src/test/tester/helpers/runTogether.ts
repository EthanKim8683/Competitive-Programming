import TesterRunResult from "../types/TesterRunResult";
import TesterRunTask from "../types/TesterRunTask";

// Short circuits Promise.all when a task completes with error(s), while
// distinguishing from unhandled errors.
class HandledError<T> extends Error {
	constructor(readonly result: T) {
		super();
	}
}
export default async <T extends any[]>(tasks: {
	[K in keyof T]: ReturnType<TesterRunTask<T[K]>>;
}): Promise<TesterRunResult<T>> =>
	Promise.all(
		tasks.map((task) =>
			task.promise.then((result) => {
				if (!result.success) throw new HandledError<typeof result>(result);
				return result;
			})
		)
	)
		.catch((err) => {
			for (const task of tasks) task.kill();
			if (!(err instanceof HandledError)) throw err;
			return err.result;
		})
		.then((result) => ({ success: true, result: result as T }));
