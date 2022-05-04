# [Dynamic Programming lecture #1 - Fibonacci, iteration vs recursion](https://www.youtube.com/watch?v=YBSt1jYwVfU)

## Look-for's:
- *'What is important so far?'*
- Base case:
  - Initial states
  - Uninitialized values based on what is being found
- Transitions:
  - Given previous sub-problems, how to solve for current sub-problem

## When to use DP & check-before's:
- Counting something, often the number of ways
  - Combinatorics
- Minimize/maximize certain value
  - Greedy
- Yes/no questions
  - Greedy

## Iteration vs Recursion:
- Iteration:
  - Speed
  - Easier complexity
  - Shorter code
  - Harder techniques can be applied
- Recursion:
  - Easier to apply
  - Fewer states
  - Order doesn't matter
  - (Compatible with DFS?)

## Visualization:
- Using a tree-like structure:
  - Helps understand what affects each sub-problem
  - Helps find repeated sub-problems
  - Errichto uses this to find a repeated sub-problem at [4:46](https://youtu.be/YBSt1jYwVfU?t=286) for his Fibonacci solution