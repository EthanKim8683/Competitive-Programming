import crypto from "crypto";

// https://stackoverflow.com/a/28061457/19662543
// export default () => {
// 	return crypto.randomBytes(4).readUInt32BE();
// };

export default <T extends Partial<{ x: string; y: string }>>(init: T) => {};
