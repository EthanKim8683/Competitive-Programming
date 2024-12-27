export type ClassProperties<T> = {
	[K in keyof T]: K extends (...args: unknown[]) => unknown ? never : T[K];
};
