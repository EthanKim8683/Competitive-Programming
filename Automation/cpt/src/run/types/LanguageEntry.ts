// Language entries generate compile and spawn arguments to run a file given
// its path.
type LanguageEntry = (filePath: string) => {
	compileArgs?: string[];
	spawnArgs: string[];
};
export default LanguageEntry;
