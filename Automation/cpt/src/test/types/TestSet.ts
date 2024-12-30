import z from "zod";
import testSetSchema from "../schemas/generatorTestSetSchema";

type TestSet = z.infer<typeof testSetSchema>;
export default TestSet;
