# Competition Problems Status
Problem|Correct cases|Attempts|Notes
-|-|-|-
A|AC|1|
B|DNF|0|
C|AC|4|
D|AC*|3|Carries can be divided into "chunks" of carries, consisting of `(0, 1)`, `(1, 0)` or `(1, 1)` and beginning with only `(1, 1)` where `(a, b)` denotes `x[i] = a and y[i] = b`. For each number of gaps (from `0` to `k - 1`), find number of ways to divide chunks and divide gaps, then add to result. Understand that the number of ways to divide chunks and the number of ways to divide gaps do not require substantial calculation.
*After competition