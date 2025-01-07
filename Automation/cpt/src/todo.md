# To-do

- Design inspect menu
- Replace error message causes with more descriptive ones
- Throw proper errors in `program()` in program.ts
- Assign each key in test sets a "score"
    - Weighted average (`avg' = p * avg + (1 - p) * new`)
    - Initially 0.5
    - Passing the corresponding test case -> `new = 1`
    - Failing the test case -> `new = 0`
