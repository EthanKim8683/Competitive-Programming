import TesterInitTaskErrorHandler from "../types/TesterInitTaskErrorHandler";
import isSystemError from "../utils/isSystemError";

export default (config: {
		dirExistenceErrorSymbol?: string;
		dirAccessErrorSymbol?: string;
		fileExistenceErrorSymbol?: string;
		fileAccessErrorSymbol?: string;
	}): TesterInitTaskErrorHandler =>
	(reason: Error, initErrorSymbol: string): string | undefined => {
		if (!isSystemError(reason)) return;

		return (
			{
				scandir: {
					ENOENT: config.dirExistenceErrorSymbol,
					EACCES: config.dirAccessErrorSymbol,
				} as Record<string, string | undefined>,
				open: {
					ENOENT: config.fileExistenceErrorSymbol,
					EACCES: config.fileAccessErrorSymbol,
				} as Record<string, string | undefined>,
			}[reason.syscall]?.[reason.code] ?? initErrorSymbol
		);
	};
