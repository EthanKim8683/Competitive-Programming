# Greedy
## Remove complexity:
- This one's kind of synonymous with sorting, so the problem should have some degree of "order doesn't matter"
- Effectively you could simplify a problem a bit by sorting a component of it
  - For example, if you have `n` things to choose from, and each thing has two attributes, you could sort along one of the attributes and do whatever operation on the other.
  - It introduces an invariant: any element will have more (or just as much) of something than all the ones before it (or after it)
  - My solution to [1801B - Buying gifts](https://codeforces.com/problemset/problem/1801/B) makes use of this idea:
    - By processing the departments in decreasing order of `a` and increasing order of `b` (in this order of significance), we can ensure that for each `a`/`b` pair, Sasha buys the gift for friend `b` from all departments of greater `a` (invariant)
    - This is useful because it makes it easy to keep track of the maximum `a`, minimum maximum `b` and possible maximum `b`'s all at once for each department, which is all that is needed to find an optimal solution to the problem
## Modify subproblem:
- Similar to dynamic programming, if we have a solution to a previous subproblem, and conditions allow it, we can simply "modify" the previous solution
- This is considered more advantageous than dynamic programming in cases where states are dependent on too many variables or if the constraints are too small
- An example is my solution to the problem [1249D2 - Too Many Segments (hard version)](https://codeforces.com/problemset/problem/1249/D2):
  - The problem could be thought of as repeatedly modifying subproblems where each subproblem contains all segments—[ordered by increasing order of right bound and left bound (in this order of significance)](#remove-complexity)—until a certain index
  - The solution to the subproblem containing the first segment is to remove no segments
  - The solution to every subproblem after that is to keep the segment if keeping it doesn't introduce any bad points and remove it if it does
    - This is because the [cost](#calculate-cost) of removing the current segment is $1$ and the cost of removing any segments to allow for the inclusion of the current segment is $\ge 1$, so the obvious choice is to always remove the current segment
## Calculate cost:
- Another method often connected to sorting, if we can assign certain decisions a cost, we can greedily make the optimal decisions
  - If sorting is required, however, each decision *must* be independent, otherwise they cannot be chosen greedily
- An example of cost being used is in my solution to [922D - Robot Vacuum Cleaner](https://codeforces.com/problemset/problem/922/D):
  - Between each pair of strings $x$ and $y$, the amount of "sh" pairs that are introduced is dependent on their order: $l_s \cdot r_h$, where $l_s$ is the number of "s"'s in the left string and $r_h$ is the number of "h"'s in the right string
  - To determine whether a decision is optimal, we can simply compare its cost with the cost of carrying out the opposite decision: $x_s \cdot y_h > y_s \cdot x_h$, equivalent to checking if $x$ on the left and $y$ on the right is better than $y$ on the left and $x$ on the right
    - We can show that this satisfies independence by dividing both sides by $y_h$ and $x_h$ to get $\frac{x_s}{x_h} > \frac{y_s}{y_h}$
    - This allows us to sort, in decreasing order, each string $z$ based on its cost of $\frac{z_s}{z_h}$
## Trading:
- If there is a constraint and many indistinguishable ways of fulfulling this constraint, we can "trade" ways to achieve minimum cost
- In the problem [1251E2 - Voting (Hard Version)](https://codeforces.com/contest/1251/problem/E2), I use trading:
  - Whenever a voter needs to be paid off, we search among the existing voters for a voter that can be traded instead:
    - Their count requirement does not exceed the current count
    - Their cost is maximum
  - By trading voters (if possible), we maintain the same number of paid-off voters, so as to not dissatisfy the voters voting by reason of count, and minimize the additional cost

# Dynamic Programming
## The core idea:
- People may have varying ideas on how exactly to approach dynamic programming, but I like to believe that dynamic programming, in practice, is the result of determining what variables can and cannot be solved easily
  - For variables that can be solved easily, typically with greedy, data structures, etc., solve them normally
  - For variables than *cannot* be solved easily, keep track of every possible value of this variable among all states (typically via one dimension of an array) and determine transitions between those states
    - This is often the more talked-about aspect of dynamic programming; namely the concept of transitions and base cases

# Math
## Number Theory:
- $\gcd(a, a + b) = \gcd(a, b)$ and $\gcd(a, a - b) = \gcd(a, b)$
  - e.g. [1322C - Instant Noodles](https://codeforces.com/problemset/problem/1322/C)
## Binomial Theorem:
- The *Vandermonde identity* shows that $\sum_{j=0}^k \dbinom{m}{j} \dbinom{n}{k-j} = \dbinom{m+n}{k}$
  - If we have $n$ red balls and $m$ blue balls, and we choose from the combined $m + n$ balls $k$ of them, there are $\dbinom{m+n}{k}$ ways total. However, we can also see the problem as choosing $j$ blue balls and $k-j$ red balls for all $j \in [0,k]$. And thus, they are equal
  - e.g. [785D - Anton and School - 2](https://codeforces.com/problemset/problem/785/D)
- $\dbinom{n}{k} = 0$ for all $k$ less than $0$ or greater than $n$
  - e.g. [785D - Anton and School - 2](https://codeforces.com/problemset/problem/785/D)
## Probabilities:
- Bayes' theorem can be used to "reverse" probabilities ($P(A \mid B) \rarr P(B \mid A)$ given $P(A)$ and $P(B)$ as well)
  - $P(B \mid A) = \frac{P(A \mid B) P(B)}{P(A)}$
  - e.g. [452C - Magic Trick](https://codeforces.com/problemset/problem/452/C)
## Tid-bits:
- $x \mod y < \lceil \frac{x}{2} \rceil$, can be used to get $O(log_2N)$ complexity in some cases
  - e.g. [438D - The Child and Sequence](https://codeforces.com/problemset/problem/438/D)

# Edge Cases
## Un-multiply $0$:
- Often times, it's pretty obvious when this edge case would need to be handled.
- However, when dealing with modulos, even though most problems ignore this case (perhaps out of mercy?), it *does* still exist
- In [543D - Road Improvement](https://codeforces.com/problemset/problem/543/D)
  - One must using tree dynamic programming to solve for all roots and, in order to move the root, one must divide away the contribution of the node being moved to
  - If the contribution becomes $0 \mod 10^9+7$, it is impossible to restore the original value through division
  - I solve this problem by keeping a count of $0$'s instead of multiplying the value itself by $0$ 

# Miscellaneous
## Dependent equations:
- When an equation is dependent on two or more variables, it sometimes helps to make them *independent* and have one variable "look up" another. Sometimes this may require modifying any number of them
  - Modifying variables can be done using math, dynamic programming, greedy, etc.
  - Any transformation can be used as long as it stays true to the original equation
- An example is [2017 - Longest beautiful sequence](https://oj.uz/problem/view/IZhO17_subsequence), where each $i$ in an increasing subsequence of array indices must satisfy $\text{bitcount}(a_i \; \& \; a_{i-1}) = k_i$ (excluding the first index, of course)
  - I won't go into detail, but to make the variables independent, both $a_i$ and $a_{i-1}$ must be modified in such a way that each $a_i$ can simply look up the maximum prefix length among all $a_{i-1}$ candidates
    - In this case, it was done with dynamic programming, effectively brute forcing for all possible transformations to $a_i$ and $a_{i-1}$ such that their being equal satisfied the problem statement and did not sacrifice accuracy

## The learning process:
- Often times I find myself just practicing for the sake of practicing, which, ironically, is not good practice:
  - People practice to learn, so it is imperative that every problem is a learning experience
  - Think of practice like gathering training data for a machine learning model:
    - The model consciously, after every epoch (a day, a week, etc. for us), backpropogates everything it has learned
    - Every sample has an impact on the final model—no sample goes to waste
    - Samples are used to find a correlation between variables, so look for patterns as you go!
## Explain before submitting:
- When practicing, it's a good idea to explain how a solution works *before* submitting
  - If it works, your brain will naturally come up with plausible explanations for why it worked; it's just easier that way
  - However, this is under the presumption that it *did* work and is not very useful during the problem-solving process when it is not yet known *if it will* work
  - What I do is, during practice, I type out my explanation in a comment below the program before submitting
## Naming concepts:
- It can help to assign names to patterns you see; they don't even have to be real algorithms!
  - The idea is similar to that of memoization, where instead of re-inventing an idea (and associated observations) every time, one assigns it a *name* to be recalled in the future
  - Some examples are [removing complexity](#remove-complexity), [modifying subproblem](#modify-subproblem), and [calculating cost](#calculate-cost), which I regularly recall when solving greedy problems