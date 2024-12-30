import z from "zod";
import generatorTestSetSchema from "../schemas/generatorTestSetSchema";

type GeneratorTestSet = z.infer<typeof generatorTestSetSchema>;
export default GeneratorTestSet;
