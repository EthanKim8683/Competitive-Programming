import Runner from "../../run/Runner";

export default async (filePaths: string[]): Promise<Runner[]> =>
	Promise.allSettled(
		filePaths.map((filePath) => (async () => new Runner(filePath))())
	).then((results) =>
		results.map((result) => {
			if (result.status === "rejected")
				throw new Error("Could not make all runners", { cause: results });
			return result.value;
		})
	);
