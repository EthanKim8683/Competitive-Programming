# Competition Problems Status
Problem|Correct cases|Attempts|Notes
-|-|-|-
A|AC|1|`r-l-c(l,r)`=# of repeats, non-decreasing with respect to `r` for all `l`.
B|AC|1|Smallest offset achievable is `gcd` of all `a`.
C|AC|1|Inequalities satisfying `!(a[u] <= a[v] && a[v] <= a[w])` are `a[u] < a[v] && a[v] > a[w]` and `a[u] > a[v] && a[v] < a[w]`, meaning all `a` are either a minimum or maximum. Assuming all `a` are sorted, a maximum before a minimum would be nonoptimal so minimums are represented as a contiguous prefix and maximums as the remaining suffix. Brute forcing for all prefixes yields an answer.
D|AC|1*|Find all base cases where removing a peg ends the game. Use permutations to find the number of ways to get to this base case. Understand that there are only few base cases and that transitions don't need to be substantially calculated for.
E|DNF|0|N/A
F|DNF|0|N/A
G1|DNF|0|N/A
G2|DNF|0|N/A
G3|DNF|0|N/A
H|DNF|0|N/A
*After competition