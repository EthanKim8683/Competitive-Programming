import z from "zod";
import samplesTestSetSchema from "./samplesTestSetSchema";
import generatorTestSetSchema from "./generatorTestSetSchema";
import interactorTestSetSchema from "./interactorTestSetSchema";

export default z.union([
	samplesTestSetSchema,
	generatorTestSetSchema,
	interactorTestSetSchema,
]);
