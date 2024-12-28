import spawnUsingArgs from "./spawnUsingArgs";

export default (args: string[]) =>
	(stdio?: Parameters<typeof spawnUsingArgs>[1]) =>
		spawnUsingArgs(args, stdio);
