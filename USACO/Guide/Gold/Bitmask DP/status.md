# Practice Problems Status
Problem|Rating|Correct cases|Attempts|Notes
-|-|-|-|-
Hamiltonian Flights|Easy|AC|3|N/A
Matching|Easy|AC|3|N/A
Team Building|Easy|AC|4|N/A
Guard Mark|Easy|AC|3|N/A
Moovie Mooving|Easy|AC|1|N/A
Uddered but not Herd|Normal|AC|1|N/A
Elevator Rides|Normal|AC|1|N/A
2014 - Bank|Normal|AC|2|N/A
Cat and Mice|Normal|AC|1|Binary search for minimum time.
Maximum Independent Set|Hard|AC|1|Meet in the middle. Optimization can be made using bitmasks to prevent transitions to nodes adjacent to visited nodes.
2017 - Longest beautiful sequence|Hard|AC|2|Understand that between two integers `a` and `b`, it is possible to make `a` equal `b` using an `x` where `a ^ x == b`. Notably, this comes with a neat property such that `bitcount(a & (a ^ x)) == bitcount(a & b)`, meaning dynamic programming can be used on an independent `a` (to find `a ^ x`) and lookup-ed for `b`. This can be further optimized since `x` can be split in two, as `(low(a) ^ low(x) == low(b) && upp(a) ^ upp(x) == upp(b)) == (a ^ x == b)`. Both sides of `low(a) ^ low(x) == low(b)` can be `xor`-ed by `low(x)` to produce `low(a) == low(b) ^ low(x)`. Now, `low(a) | upp(a) ^ upp(x)` can be lookup-ed while `upp(b) | low(b) ^ low(x)` can be looking up. This results in a final complexity of `O(N * K)`.
2016 - Burza|Hard|DNF|0|N/A
Redistributing Gifts|Hard|DNF|0|N/A