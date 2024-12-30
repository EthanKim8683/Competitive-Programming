import z from "zod";
import samplesTestSetSchema from "../schemas/samplesTestSetSchema";

type SamplesTestSet = z.infer<typeof samplesTestSetSchema>;
export default SamplesTestSet;
