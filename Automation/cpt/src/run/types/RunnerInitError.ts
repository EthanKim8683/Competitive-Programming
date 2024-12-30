import Runner from "../Runner";
import quote from "../../utils/quote";
import RunnerInitErrorCode from "./RunnerInitErrorCode";

export default class RunnerInitError extends Error {
	public static Code = RunnerInitErrorCode;

	constructor(
		readonly runner: Runner,
		readonly code: RunnerInitErrorCode,
		options?: ErrorOptions
	) {
		super(
			(() => {
				switch (code) {
					case RunnerInitErrorCode.ACCESS_ERROR:
						return `Could not access file: ${quote(runner.filePath)}`;
					case RunnerInitErrorCode.LANGUAGE_INFERENCE_ERROR:
						return `Could not infer language of file: ${quote(runner.filePath)}`;
					case RunnerInitErrorCode.LANGUAGE_SUPPORT_ERROR:
						return `Unsupported language: ${quote(runner.language)}`;
					case RunnerInitErrorCode.LANGUAGE_ENTRY_ERROR:
						return `Could not generate compile/spawn arguments for language: ${quote(runner.language)}`;
					case RunnerInitErrorCode.COMPILATION_ERROR:
						return `Could not compile file: ${quote(runner.filePath)}`;
				}
			})(),
			options
		);
	}
}
