import crypto from "crypto";

// https://stackoverflow.com/a/28061457/19662543
export default () => crypto.randomBytes(4).readUInt32BE();
