export type LanguageEntry = (filePath: string) => {
	compileArgs?: string[];
	spawnArgs: string[];
};
