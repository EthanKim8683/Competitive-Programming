import RunnerRun from "../../../run/types/RunnerRun";
import RunnerRuntimeError from "../../../run/types/RunnerRuntimeError";
import TesterTaskResult from "../types/TesterTaskResult";
import TesterRunTask from "../types/TesterRunTask";

const runRunner = (
	run: RunnerRun,
	errorToSymbol: {
		default: string;
		runtimeError?: string;
	}
): { promise: Promise<TesterTaskResult<undefined>>; kill: () => void } => ({
	promise: run.promise
		.then(() => ({
			success: true as const,
			result: undefined,
		}))
		.catch((err) => {
			if (!(err instanceof RunnerRuntimeError)) throw err;
			return {
				success: false,
				reasons: { [errorToSymbol.runtimeError ?? errorToSymbol.default]: err },
			};
		}),
	kill: () => run.kill(),
});
// Assert type
runRunner as TesterRunTask<undefined>;
export default runRunner;
