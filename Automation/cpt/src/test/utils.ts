import crypto from "crypto";

// https://stackoverflow.com/a/28061457/19662543
export const randomUnsigned = () => crypto.randomBytes(4).readUInt32BE();

// https://stackoverflow.com/a/43044960/19662543
export const randomUnsigneds = (n: number) =>
	Array.from({ length: n }, () => randomUnsigned());
