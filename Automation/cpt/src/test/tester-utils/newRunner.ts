import Runner from "../../run/Runner";

export default async (
	...args: ConstructorParameters<typeof Runner>
): Promise<Runner> => new Runner(...args);
