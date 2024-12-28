import randomUnsigned from "./randomUnsigned";

// https://stackoverflow.com/a/43044960/19662543
export default (n: number) => Array.from({ length: n }, () => randomUnsigned());
