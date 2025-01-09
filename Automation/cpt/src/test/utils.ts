import crypto from "crypto";

import {
	AwaitedKillablePromise,
	KillablePromise,
} from "../utils/KillablePromise";
import {
	InitResult,
	ResultWithVerdict,
	TestCaseResult,
	WithVerdict,
} from "./types";
import program from "../run/program";
import { Result } from "../utils/errors";
import readDir from "../run/readDir";

// https://stackoverflow.com/a/28061457/19662543
export const randomUnsigned = () => crypto.randomBytes(4).readUInt32BE();

// https://stackoverflow.com/a/43044960/19662543
export const randomUnsigneds = (n: number) =>
	Array.from({ length: n }, () => randomUnsigned());

export async function initTogether<T extends ResultWithVerdict<any>[]>(tasks: {
	[K in keyof T]: {
		initer: T[K];
		symbol: string;
	};
}): Promise<{ success: boolean; results: T }> {}
