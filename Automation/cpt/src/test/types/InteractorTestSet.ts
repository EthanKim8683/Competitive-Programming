import z from "zod";
import interactorTestSetSchema from "../schemas/interactorTestSetSchema";

type InteractorTestSet = z.infer<typeof interactorTestSetSchema>;
export default InteractorTestSet;
