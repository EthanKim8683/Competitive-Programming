# Practice Problems Status
Problem|Rating|Correct cases|Attempts|Notes
-|-|-|-|-
Subtree Queries|Easy|AC|1|N/A
Company Queries II|Easy|AC|2|N/A
Distance Queries|Easy|AC|1|N/A
Static RMQ|Easy|AC|2|N/A
Distinct Colors|Easy|AC|3|N/A
Path Queries|Normal|AC|2|N/A
Cow Land|Normal|AC|1|N/A
Milk Visits|Normal|AC|3|N/A
Promotion Counting|Normal|AC|1|N/A
Count Descendants|Normal|AC|2|N/A
Distance Queries on a Tree|Hard|AC|1|Understand that the distance between two nodes in a tree is the sum of the distances of either node with their $\text{LCA}$. This allows us to simply keep track of the distance from root for each node, which can be updated using a segment tree for each query. Meanwhile $\text{LCA}$ queries can be answered using sparse table or binary lifting.
2009 - Regions|Hard|AC|1|Understand that, if we answer queries from the "point of view" of $r _ 1$ or $r _ 2$, depending on which region has fewer employees, the maximum total number of operations will not cause the program to exceed the time limit. Assuming there are only $\sqrt Q$ regions, each region can have $\frac{N}{\sqrt Q}$ employees. For all pairs of regions (for all queries), that is $\frac{N}{\sqrt Q} \times Q = N \sqrt Q$ operations total. And if each operation only takes $O(\log _ 2 N)$ time, the final complexity is $O(N \log _ 2 {N} \sqrt Q)$.