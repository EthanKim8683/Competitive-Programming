import Runner from "../Runner";
import RunnerRun from "./RunnerRun";

export default class RunnerRuntimeError extends Error {
	readonly runner: Runner;

	// This constructor should only be called by `RunnerRun`.
	constructor(
		readonly run: RunnerRun,
		readonly code: number | null,
		readonly signal: NodeJS.Signals | null,
		options?: ErrorOptions
	) {
		super(
			signal
				? `${run.runner} killed with signal: '${signal}'`
				: `${run.runner} exited with non-zero exit code: ${code}`,
			options
		);
		this.runner = run.runner;
	}
}
