import RunnerInitError from "../../../run/types/RunnerInitError";
import TesterInitTaskErrorHandler from "../types/TesterInitTaskErrorHandler";

export default (config: {
		accessErrorSymbol?: string;
		languageInferenceErrorSymbol?: string;
		languageSupportErrorSymbol?: string;
		languageEntryErrorSymbol?: string;
		compilationErrorSymbol?: string;
	}): TesterInitTaskErrorHandler =>
	(reason: Error, initErrorSymbol: string): string | undefined => {
		if (!(reason instanceof RunnerInitError)) return;
		return (
			{
				[RunnerInitError.Code.ACCESS_ERROR]: config.accessErrorSymbol,
				[RunnerInitError.Code.LANGUAGE_INFERENCE_ERROR]:
					config.languageInferenceErrorSymbol,
				[RunnerInitError.Code.LANGUAGE_SUPPORT_ERROR]:
					config.languageSupportErrorSymbol,
				[RunnerInitError.Code.LANGUAGE_ENTRY_ERROR]:
					config.languageEntryErrorSymbol,
				[RunnerInitError.Code.COMPILATION_ERROR]: config.compilationErrorSymbol,
			}[reason.code] ?? initErrorSymbol
		);
	};
