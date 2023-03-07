# Practice Problems Status
Problem|Rating|Correct cases|Attempts|Notes
-|-|-|-|-
The Fair Nut and Rectangles|Easy|AC|3|While a deque (monotone chain) could work in this case, because of the monotonicity of the queries and insertions, it's better practice to use a more general data structure: Li Chao tree, as used in my solution. It supports `O(log(N))` insertions and queries and is based on a segment tree. Most cases would require either a sparse segment tree or coordinate compression, again used in my solution.
2010 - Commando|Easy|AC|15|There are probably faster/less memory intensive solutions, especially considering the memory and time constraints, but again, I chose Li Chao tree for its utility. I would not recommend doing this in the future, but as I am studying for USACO and USACO grading servers typically have reasonable (if not generous) time and memory limits, this is acceptable.
2004 - Two Sawmills|Easy|AC|2|This time, Li Chao seemed to perform fine, possibly because I used a more efficient (memory and overhead) iterative version, despite the tight constraints.
Houses and Schools|Easy|AC|4|Understand that Li Chao, although much more general, is probably not USACO Guide's intended solution. In fact, it is stated that all problems in the list can be solved using monotonic convex hull trick. With this in mind, I tried solving this problem as such. Separating the variables and then grouping them by dependency is a decent problem solving strategy, though we'll have to see how well this holds up later.
2009 Harbingers|Normal|AC|1|Understand that a kind of "heavy-light decomposition" can be used here to turn the tree into linear pieces, on which stacks can be used (convex hull trick).
Bear and Bowling 4|Normal|DNF|0|N/A
2002 - Batch Scheduling|Normal|DNF|0|N/A
2014 - Split the Sequence|Normal|DNF|0|N/A
2011 - Lightning Conductor|Normal|DNF|0|N/A
2006 - Frogs|Normal|DNF|0|N/A
Circular Barn|Normal|DNF|0|N/A
Falling Portals|Normal|DNF|0|N/A
2017 - Long-Distance Coach|Hard|DNF|0|N/A