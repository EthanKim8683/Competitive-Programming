type TesterInitTask<T> = {
	promise: Promise<T>;
	initErrorSymbol: string;
	runnerAccessErrorSymbol?: string;
	runnerLanguageInferenceErrorSymbol?: string;
	runnerLanguageSupportErrorSymbol?: string;
	runnerLanguageEntryErrorSymbol?: string;
	runnerCompilationErrorSymbol?: string;
};
export default TesterInitTask;
