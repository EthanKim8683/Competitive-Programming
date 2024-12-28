import path from "path";

export default (filePath: string): string | undefined => {
	let language: string | undefined;

	// For files that specify language via filename (name.language.ext),
	language ??= /(?<=[^./]*\.)[^./]*(?=\.[^./]*$)/.exec(filePath)?.[0];

	language ??= {
		".cpp": "c++20",
		".py": "python3",
	}[path.extname(filePath)];

	return language;
};
