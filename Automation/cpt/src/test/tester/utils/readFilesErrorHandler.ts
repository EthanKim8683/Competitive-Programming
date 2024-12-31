import TesterInitTaskErrorHandler from "../types/TesterInitTaskErrorHandler";
import isSystemError from "../../../utils/isSystemError";
import { ParseIntError } from "../../../utils/parseIntWithError";

export default (config: {
		dirExistenceErrorSymbol?: string;
		dirAccessErrorSymbol?: string;
		fileAccessErrorSymbol?: string;
		fileNameErrorSymbol?: string;
	}): TesterInitTaskErrorHandler =>
	(reason: Error, initErrorSymbol: string): string | undefined => {
		if (isSystemError(reason)) {
			return (
				{
					scandir: {
						ENOENT: config.dirExistenceErrorSymbol,
						EACCES: config.dirAccessErrorSymbol,
					} as Record<string, string | undefined>,
					open: {
						EACCES: config.fileAccessErrorSymbol,
					} as Record<string, string | undefined>,
				}[reason.syscall]?.[reason.code] ?? initErrorSymbol
			);
		}

		if (reason instanceof ParseIntError) {
			return config.fileNameErrorSymbol ?? initErrorSymbol;
		}
	};
