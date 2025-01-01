import TesterTaskResult from "../types/TesterTaskResult";
import TesterRunTask from "../types/TesterRunTask";

// Short circuits Promise.all when a task completes with error(s), while
// distinguishing from unhandled errors.
class HandledError<T> extends Error {
	constructor(readonly result: T) {
		super();
	}
}
// Assumes tasks are dependent. Analogous to `Promise.all`.
export default async <T extends any[]>(tasks: {
	[K in keyof T]: ReturnType<TesterRunTask<T[K]>>;
}): Promise<TesterTaskResult<T>> =>
	Promise.all(
		tasks.map((task) =>
			task.promise.then((result) => {
				if (!result.success) throw new HandledError<typeof result>(result);
				return result;
			})
		)
	)
		.then((result) => ({ success: true, result: result as T }))
		.catch((err) => {
			for (const task of tasks) task.kill();
			if (!(err instanceof HandledError)) throw err;
			return err.result;
		});
