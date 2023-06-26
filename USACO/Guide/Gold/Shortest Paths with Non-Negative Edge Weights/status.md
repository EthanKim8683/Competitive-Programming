# Practice Problems Status
Problem|Rating|Correct cases|Attempts|Notes
-|-|-|-|-
Shortest Routes II|Easy|AC|3|N/A
Shortest Routes I|Easy|AC|3|N/A
Flight Discount|Easy|AC|5|N/A
Milk Pumping|Easy|AC|1|N/A
Why Did the Cow Cross the Road|Easy|AC|1|N/A
Fine Dining|Easy|AC|1|N/A
Shortcut|Normal|AC|1|N/A
Not Escaping|Normal|AC|3|N/A
Investigation|Normal|AC|1|N/A
Flight Routes|Normal|AC|2|N/A
Robot Turtles|Normal|AC|2|N/A
Remainder Game|Hard|AC|1|Understand that it would be optimal for the `k` to be applied in decreasing order, as a number `x` modulo `b` modulo `a` is still `x` modulo `b` if `b <= a`. If chosen in such order, each `k` would only need to be used at most once, this means that we can effectively solve for each bit of the answer greedily in decreasing order of significance. Using dynamic programming we can keep track for each index `i` the minimum bit that still turns `a[i] % k[1] % k[2] % ... % k[n]` (where each `k[j]` is part of the set of `k` chosen already) into `b[i]` and repeatedly take the maximum among all such `i` as `k`.
2011 - Crocodile|Hard|AC|5|N/A
2018 - Commuter Pass|Hard|AC|1|N/A
2021 - Robot|Hard|AC|3|Understand that a dynamic programming approach can be used to solve the problem, where each state is defined by the color of edge used to get there (or none at all). This is because, at each node, it is possible to change either one road's color, or the other same-color roads' color. And when doing the latter, the cost is decreased if the road used to get there was of the same color, and had been changed.
2011 - Find the Path|Hard|AC|3|Understand that a simple Dijkstra's on all critical points suffices. Critical points can be found using sweep line.
2012 - Shortest Paths|Hard|AC|5|Understand that a shortest path from `a` to `b` at every adjacent pair of nodes `i` and `j` is equivalent to the union of the shortest path from `a` to `i` and `b` to `j`. By this logic, we can find all shortest paths originating in both `a` and `b` and brute force for all such `i` and `j`.
2015 - Circus|Very Hard|DNF|0|N/A