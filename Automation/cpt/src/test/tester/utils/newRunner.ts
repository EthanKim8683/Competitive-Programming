import Runner from "../../../run/Runner";
import RunnerInitError from "../../../run/types/RunnerInitError";
import TesterInitResult from "../types/TesterInitResult";
import TesterInitTask from "../types/TesterInitTask";

const newRunner = async (
	args: ConstructorParameters<typeof Runner>,
	errorToSymbol: {
		default: string;
		accessError?: string;
		languageInferenceError?: string;
		languageSupportError?: string;
		languageEntryError?: string;
		compilationError?: string;
	}
): Promise<TesterInitResult<Runner>> => {
	try {
		return {
			success: true,
			result: new Runner(...args),
		};
	} catch (err: unknown) {
		if (err instanceof RunnerInitError)
			return {
				success: false,
				reasons: {
					[{
						[RunnerInitError.Code.ACCESS_ERROR]: errorToSymbol.accessError,
						[RunnerInitError.Code.LANGUAGE_INFERENCE_ERROR]:
							errorToSymbol.languageInferenceError,
						[RunnerInitError.Code.LANGUAGE_SUPPORT_ERROR]:
							errorToSymbol.languageSupportError,
						[RunnerInitError.Code.LANGUAGE_ENTRY_ERROR]:
							errorToSymbol.languageEntryError,
						[RunnerInitError.Code.COMPILATION_ERROR]:
							errorToSymbol.compilationError,
					}[err.code] ?? errorToSymbol.default]: err,
				},
			};

		throw err;
	}
};
// Assert type
newRunner as TesterInitTask<Runner>;
export default newRunner;
