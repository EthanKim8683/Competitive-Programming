import Runner from "../Runner";
import RunnerRunPromise from "./RunnerRunPromise";

export default class RunnerRuntimeError extends Error {
	readonly runner: Runner;

	constructor(
		readonly runPromise: RunnerRunPromise,
		readonly code: number | null,
		readonly signal: NodeJS.Signals | null,
		options?: ErrorOptions
	) {
		super(
			signal
				? `${runPromise.runner} killed with signal: '${signal}'`
				: `${runPromise.runner} exited with non-zero exit code: ${code}`,
			options
		);
		this.runner = runPromise.runner;
	}
}
