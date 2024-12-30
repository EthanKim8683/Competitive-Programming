import z from "zod";
import isValidPath from "is-valid-path";

export default z
	.string()
	.refine((path) => isValidPath(path), { message: "Invalid path" });
