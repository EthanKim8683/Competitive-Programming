# Practice Problems Status
Problem|Rating|Correct cases|Attempts|Notes
-|-|-|-|-
Lomsat gelral|Normal|AC|1|N/A
Disruption|Normal|AC|1|N/A
2011 - Tree Rotations|Normal|AC|2|Using `ordered_set`s for each node and small-to-large merging for each branch, minimizing between rotating the branch or not. Note that inversions are independent per branch.
2011 - Race|Normal|AC|4|Using a map for each node, keeping track of every distance from root possible in said node's subtree with its corresponding minimum depth allows lookups during merges for minimal paths that sum up to the given `k`; minimize among all merges.
2020 - Joitter|Hard|AC|8|Understand that a `DSU`-like approach can be used here, small-to-large merging at each union. An edge occurs when a pair of nodes are connected in either direction, and a connected component results in `n * (n - 1)` directed edges where `n` is the size of the component. If a directed edge ends in a connected component, it results in a total of `n` directed edges ending said component. With these rules in mind, simply removing overlapping edges for each union and "merging" the connected components (and their properties) suffices.
2009 - Loza|Hard|AC|4|Understand that each family subtree has levels, and of those levels are lower and upper bounds representing the minimum and maximum horizontal position the subtree occupies. Using these bounds, we can effectively find the required distance any two child subtrees must be placed apart such that they do not collide. Calculating these bounds for each subtree is a matter of merging the child subtrees, which can be done using small-to-large merging.
2019 - Virus|Very Hard|DNF|0|N/A