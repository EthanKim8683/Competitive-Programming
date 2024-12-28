import Runner from "../Runner";
import quote from "../../utils/quote";

enum Code {
	ACCESS_ERROR = "ACCESS_ERROR",
	LANGUAGE_INFERENCE_ERROR = "LANGUAGE_INFERENCE_ERROR",
	LANGUAGE_SUPPORT_ERROR = "LANGUAGE_SUPPORT_ERROR",
	LANGUAGE_ENTRY_ERROR = "LANGUAGE_ENTRY_ERROR",
	COMPILATION_ERROR = "COMPILATION_ERROR",
}
export default class extends Error {
	public static Code = Code;

	constructor(
		readonly runner: Runner,
		readonly code: Code,
		options?: ErrorOptions
	) {
		super(
			(() => {
				switch (code) {
					case Code.ACCESS_ERROR:
						return `Could not access file: ${quote(runner.filePath)}`;
					case Code.LANGUAGE_INFERENCE_ERROR:
						return `Could not infer language of file: ${quote(runner.filePath)}`;
					case Code.LANGUAGE_SUPPORT_ERROR:
						return `Unsupported language: ${quote(runner.language)}`;
					case Code.LANGUAGE_ENTRY_ERROR:
						return `Could not generate compile/spawn arguments for language: ${quote(runner.language)}`;
					case Code.COMPILATION_ERROR:
						return `Could not compile file: ${quote(runner.filePath)}`;
				}
			})(),
			options
		);
	}
}
