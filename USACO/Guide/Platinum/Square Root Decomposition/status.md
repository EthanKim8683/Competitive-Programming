# Practice Problems Status
Problem|Rating|Correct cases|Attempts|Notes
-|-|-|-|-
Dynamic Range Sum Queries|Very Easy|AC|1|By dividing the array into ranges of size `sqrt(N)`, at max `sqrt(N)` ranges and `sqrt(N)` individual elements need to be combined per query. Updates are constant time.
Points on Plane|Easy|AC|1|Understand that dividing the `X`-by-`Y` domain into `X / sqrt(X)`-by-`Y` "blocks" (where `X` is the width of the domain and `Y` is the height) and kind of zig-zagging along the blocks yields the optimal answer. This is because, when going top-to-bottom or bottom-to-top inside a block, at distance of at most `Y` is travelled along the up-down axis per block, yielding `Y * sqrt(X)` in total. Along the right-left axis, at most `sqrt(X) * N` (where `N` is the number of nodes) is travelled in total. Finally, going between blocks is at most `sqrt(X) * 2` per edge, making `sqrt(X) * 2 * (X / sqrt(X) - 1)` total. Summing all of these distances produces a total distance around `2001998000`, worst case, which is below the `25e8` limit.
2018 - Bitaro's Party|Easy|AC|47|Understand that, by keeping the `sqrt(N)` longest paths for each node, at most `Y` queries could be answered by checking each of the longest paths' sources against the the busy nodes (`Y < sqrt(N)`), resulting in `O(sqrt(N))` per query and `O(Y * sqrt(N))` in total. Meanwhile, at most `sqrt(Y)` queries would require further checking (`Y >= sqrt(N)`), resulting in `O(N)` per query and `O(sqrt(Y) * N)` in total. Building this (using priority queue; I'm sure there's a faster way) takes `O((N * sqrt(N) + M) * log2(sqrt(N)))`. The final complexity of this algorithm is `O(Y * sqrt(N) + sqrt(Y) * N + (N * sqrt(N) + M) * log2(sqrt(N)))`.
2017 - Containers|Easy|AC|1|Understand that, if `l <= sqrt(N)`, simply adding for each of the `l` indices produces `O(N * sqrt(N))` worst case. And if `l > sqrt(N)`, `d <= N / sqrt(N)`, meaning a set of indices repeating every `d` can only repeat at most `N / sqrt(N)`, allowing us to check at every index `i`, for each possible value of `d` how many containers should be placed based on `i % d`.
Holes|Easy|AC|1|Understand that blocking can be used on the domain, where each edge as a result of computation leads to a block *after* the current block. If the size of each block is `k`, each update runs in `k` and each query is `n / k`.
Ann and Books|Easy|AC|7|Understand that Mo's algorithm can be used to answer each range query and an array of counts with coordinate compression (`multiset` results in TLE) can be used to keep track of prefix sums in `O(N * sqrt(N))`.
Static Range Inversions Query|Normal|AC|1|Understand that Mo's algorithm can be used to answer each range query. Inversions are tracked using a fenwick tree, where each value is coordinate compressed. The final complexity is `O(N * sqrt(N) * log2(N))`.
Powerful Array|Normal|AC|1|Understand that Mo's algorithm can be used to answer each range query. An array of counts is kept and every addition or removal uses the count to add or subtract from the result. The complexity is `O(N * sqrt(N))`
2019 - Bridges|Hard|AC|5|Understand that batching by updates can be used to solve the problem under the time limit. Answering queries while performing DSU on edges sorted in decreasing order of weight is usually enough to solve the problem naively for each query in `O(M * log(M) + Q * log(Q))`. However, as there are updates, batching must be used. By "disconnecting" each edge updated in the current batch, then manually "re-connecting" them for each query, at most `K` edges, where `K` is the batch size, are re-connected per query for a total complexity of `O(K * Q)`. Combined with the `N / K` batch resets, `O(M * log(M))` each, the final complexity is `O(K * Q + N / K * (M * log(M)) + K * log(K))`.
2018 - Snake Escaping|Hard|AC|1|Understand that it is fast (`O(L * (2 ^ L))`) and memory-efficient to calculate the sum when only two symbols (one of '0', '1' or '?') are present. Combine this with the fact that the maximum distance until the query consists of only two symbols is `floor(L / 3)` and that any other symbol `x` can be calculated for using PIE in `2 ^ c`, where `c` is the count of symbol `x`, the final complexity of the solution is `O(L * (2 ^ L) + C * Q)`, where `C` is `2 ^ floor(L / 3)`.
Train Tracking|Very Hard|DNF|0|N/A
Fluid Dynamics|Very Hard|DNF|0|N/A
Arithmetic Subtrees|Very Hard|DNF|0|N/A
2019 - Examination|Normal|DNF|0|N/A
2009 - Regions|Normal|DNF|0|N/A
New Barns|Hard|DNF|0|N/A
Tree Queries|Hard|DNF|0|N/A
The Tree|Hard|DNF|0|N/A
Tree Game|Hard|DNF|0|N/A
Shopping Time|Hard|DNF|0|N/A
Fencing the Herd|Hard|DNF|0|N/A
The Awesomest Vertex|Very Hard|DNF|0|N/A
2011 - Dancing Elephants|Very Hard|DNF|0|N/A
Cow At Large|Very Hard|DNF|0|N/A
2015 - Teams|Very Hard|DNF|0|N/A