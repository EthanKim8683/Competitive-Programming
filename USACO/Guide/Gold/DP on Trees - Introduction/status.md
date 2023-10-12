# Practice Problems Status
Problem|Rating|Correct cases|Attempts|Notes
-|-|-|-|-
Tree Matching|Easy|AC|1|N/A
Independent Set|Easy|AC|1|N/A
Barn Painting|Easy|AC|1|N/A
Distance in Tree|Normal|AC|1|N/A
Village (Minimum)|Normal|AC|2|Understand that the tree may be divided into little sub-groups, which can be optimized for using DP. In addition, among the sub-groups, villagers may be redistributed cyclically. See code for more details.
Nastia Plays with a Tree|Normal|AC|2|Understand that there are two cases per state: a "bend", where a node is connected to at most two of its children, and a "bamboo" where a node is connected to at most one of its children and at most one parent. A bend cannot be connected to its parent because that would turn a bend into a branch. Using these two states and their respective rules, we can use DP on trees to find the optimal solution.
Parade|Normal|AC|1|Understand that DP can be used to determine which branch is optimal (if any) at each branching. DP can also be used to guarantee a parade doesn't start and end at the same node.
Berland Federalization|Normal|AC|1|DP can be used to check all state size possibilities at each node, then minimizing the cost of reaching size `k` at each node yields the optimal answer. Each state can also keep track of the transition used to reach it to retrace the steps that led to the answer.
Parsa's Humongous Tree|Normal|AC|1|Understand that only the "extreme" values need to be considered, like the minimum and maximum of each node on an edge. Using DP with the differences of these extrema as transitions yields the optimal answer.
Delegation|Hard|AC|2|Understand that running a complete search on all `k` such that `k` divides `n - 1` requires at most `128` traversals (as shown here: [https://ideone.com/IXokDN](https://ideone.com/IXokDN)). Using dynamic programming, we can check if the tree can be divided into paths of length of exactly `k` for each `k`.
2004 - Spies|Hard|AC|4|Understand that, since the problem describes a functional graph, we can split each cycle into trees, solve on each tree, then combine them back using dynamic programming. For the trees, the states are assigning/not assigning for each node, while the cycles' states contain whether or not the "first" node was assigned, as well as the most recent node, allowing the cycle to be closed in the end.
2008 - Mafia|Hard|DNF|0|N/A