# Practice Problems Status
Problem|Rating|Correct cases|Attempts|Notes
-|-|-|-|-
339D|1700|AC|2|Understand that the data may follow a segment tree-like structure, where each update only takes `O(N)` operations to do. 
1359C|1700|AC|1|Understand that each odd iteration of the procedure deviates from `(h + c) / 2` less and less, and since `h` is always positive, the function is monotonically decreasing. This means binary search may be used to find the most optimal solution.
478C|1800|AC|4|Understand that all of the smallest color should be used entirely. The question is distributing the balloons among groups of `2` (and `1` of the other two colors) or `1` (and `2` of the other two colors). This can be determined through binary search, as the number of remaining balloons of the other two colors should be minimized. Then, distribute the number of ballons allocated to the remaining colors such that their difference is minimized. Then, with another binary search, find the best grouping of `1`s and `2`s for the second color such that the number of remaining ballons of the third color is minimized. Return the total number of groups.
448D|1800|AC|1|Understand that the number of table values less than `x` can be calculated in `O(N)` by summing up, for each `i` from `1` to `n` inclusive, how many multiples of `i` are less than `x`. This can be binary searched for in `O(log(N * M) * N)` time by comparing the number of table values less than `x` to `k - 1`.
1396B|1800|AC|1|Understand that a greedy approach may be proven. Assuming `s` equals the number of stones, if the first player chooses the pile with more than `floor(s / 2)` stones, they would win. This is because the second player would run out of stones before the first, being forced to choose from the smaller half of the stones. Now, if there are no piles with more than `floor(s / 2)` stones, then there are two cases: if `s` is even, a perfect matching can be applied such that each stone in one pile is matched with another stone in another pile. This would always result in the first player losing because, if the first player makes a move, the second player can always choose the matched stone. If `s` is odd, however, the "even" case is reversed, where the second player makes a move and the first player always chooses the matched stone, resulting in the first player winning.
1355C|1800|AC|1|Understand that, once the largest side `z` has been determined, the only way `x` and `y` can be chosen such that the resulting triangle is degenerate is if `x` and `y` total less than `z + 1`. This forms inequality `x + y >= z + 1`, which, combined with all other constraints on `x` and `y`, could be solved for all possible `z` in `O(D)` time. Note that a graphical approach would be tricky here; it would be more sensible to simply solve for the inequalities mathematically.
1388C|1800|AC|1|Understand that the correctness of the collected happiness indexes can be solved independently for each city. Simply checking if there are no relative increases in happiness from parent to child and if the happiness of a city is valid yields the correct answer.
1326D2|1800|AC|2|Understand that, we can greedily find the largest same-length prefix and suffix of `s`, then find the longest palindrome prefix or suffix in the remaining middle section. The reason this works is because, for every character given to the prefix/suffix length, at most one pair of characters is taken away from the middle palindrome, resulting in a net difference of at least `0`. To find the longest palindrome prefix or suffix, Knuth-Morris-Pratt can applied to the middle section. However, naively finding the maximum proper prefix of such a string would not work, as a proper prefix cannot equal the string itself. A workaround would be to concatenate the string, followed by a delimeter and ending with the string reversed. This way, an entire prefix palindrome would match with itself as a prefix of the initial string and a suffix of the reversed string.
1329A|1800|AC|3|Understand that, assuming a painting is contiguous, every length between the minimum and maximum lengths are possible (imagine a [*linear slide*](https://www.gobilda.com/4-stage-viper-slide-kit/)). To calculate the minimum length, we leave `i` space before the current coloring such that all previous `i` colors appears at least once and then calculate the maximum ending of all such colorings. To calculate the maximum length, simply leave no overlap between colorings, meaning the sum of all lengths. The solution itself can be solved greedily by positioning each coloring as far right as possible.
459D|1800|AC|1|Understand that the values of `f(1, i, a[i])` for all `i` and `f(j, n, a[j])` for all `j` can be solved and cached, each in `O(N)` time. Now it's a simple problem of range queries on all `j` for each `i` for `f(j, n, a[j]) < f(1, i, a[i])`. Since the domain of the queries updates each iteration, a point-update-range-query data structure may be used.
271D|1800|AC|15|Understand that a trie can be used to identify unique substrings. Although hashing (rolling hash) is apparently usable in this case, it's *not exact*.
1500A|1800|AC|3|Understand that, for every (`0`-indexed) index `i`, the corresponding `a[i]` must introduce exactly `i` unique sum pairs to dissatisfy `a[x] + a[y] = a[z] + a[w]`. This is because any smaller amount would mean a non-unique sum pair was found, solving the equation. This limits the maximum number of indices to be searched in order to find a solution to `a[x] + a[y] = a[z] + a[w]` to roughly `sqrt(2 * A)` (As there are only `2 * A` possible sums, so `x` iterations where `x * (x - 1) / 2 <= 2 * A`). However, in actuality it is much lower because, in order to introduce `i` unique sum pairs for each index `i`, `a[i]` must be increasing rapidly and will reach the maximum `A` value first.
1548B|1800|AC|4|Understand that, a set of numbers, all equal modulo `m`, differ from each other always by a multiple of said `m`. Therefore, the `gcd` of the differences between each adjacent number in a subarray should yield the divisor `m`. Since it must be that `m >= 2`, for each `i`, a binary search may be used to find a maximum `j`, the end of the subarray beginning at `i` such that the aforementioned condition is fulfilled. To calculate `m` quickly for each subarray, a range query data structure like sparse table (`O(1)`) or segment tree (`O(log(N))`) may be used.
1554D|1800|AC|1|Understand that, in a contiguous group of character `c` with length `l`, substrings of length `i` in range `[1, l]` occur `l - i + 1` times. Notably, the parity alternates, beginning with the parity of `l` for a substring of length `1`. With this in mind, a pair of separated contiguous groups of character `c` must have lengths `l` and `l - 1` in order for each substring from `[1, l]` to be represented an odd number of times. From here, a greedy approach may be used to divide a length `n` into `2` or more odd totals for all `n >= 2`.
220B|1800|AC|1|Understand that, when processing queries in non-decreasing order of upper bound, the range of possible lower bounds can be easily divided into three contiguous parts (in decreasing order of `l`): `f(x, l) < x`, `f(x, l) = x` and `f(x, l) > x`, where `f(x, y)` is the number of occurences of `x` from `y` as a lower bound to the current upper bound, inclusive. This can be represented by marking the rightmost `l` such that `f(x, l) = x` holds true with a `1` and the rightmost `l` where `f(x, l) > x` is true with a `-1` and using a range query data structure to produce a range sum. This ensures only `f(x, l) = x` contributes to the result because if `f(x, l) < x`, the range sum would start too far right to include the `1`, if `f(x, l) == x`, the range sum would include the `1` and the range sum would include both `1` and `-1`, summing to `0` if `f(x, l) > x`. Note that this could be updated for `a[i]` for each index `i` in `O(log(N))` using the data structure and that the values never overlap.
584D|1800|AC|2|Remember that Goldbach's conjecture states that any even number can be represented as the sum of two prime numbers. This can be applied to the problem by including one odd prime number in the answer and solving for the remaining even number. Note that the initial odd prime can be any prime number except `2`, so to make the final solve easy, the prime should be as large as possible. This could be brute forced as the largest prime gap at `1e9` is under `1000`, which, when combined with `O(sqrt(N))` prime checking, easily performs under the time limit. Finally, solving the remaining even number can also be brute forced for the a number of operations equal to the aforementioned largest prime gap.
706D|1800|AC|2|Understand that a trie data structure with counts for each node can be used to simulate a multiset. Querying for maximum `xor` can be solved greedily in `O(log(X))` by traversing the trie in descending order of significance, trying for the opposite of each bit at each index.
1367D|1800|AC|1|Understand that each index `i` in `t` has the same set of indices `j` such that `t[i] < t[j]` as its same-value counterparts. This means that each set of identical values can be distinguished by comparing their provided distance sum `b` with the distance sum to the indices of already found values. Note that this implicitly produces values of `t` in decreasing order because larger values of `t` are used to discover smaller values of `t`. With this in mind, a greedy approach may be used to then map the same-value subsets to characters.
1338B|1800|AC|2|Understand that, if, on a path from one leaf to another, every bit is positive an even number of times, the `xor` of the entire path is `0`. One way this could be achieved is as following: Describe a "flower" as a set of edges all connected to a single non-leaf node such that all edges have at least one positive bit in common, and an intersection as two flowers sharing at least one edge and one positive bit. In a tree containing no intersecting flowers, the `xor` of any path between two leaf nodes will always be `0`. This is because, any non-leaf node passed through in such a path contributes exactly two edges to said path, and if the edges share a positive bit, their `xor` will equal `0`. To produce a maximal answer, each flower will have a unique bit. To produce a minimal answer, as few unique bits will be used as possible. (Might rewrite this analysis, explanation is vague and incomplete)
1554C|1800|AC|1|Understand that, when laid out as an array, `xor`s applied to all values of `[0, m]` could be simulated through swaps, such that, at all indices to flipped in the operation, power-of-two subarrays, size dependent on the index (`1 << i`, where `i` is the index starting with `0` as the least significant bit), switch places with its opposite-bit neighbor. With this, it can be found that, when processing in decreasing order of significance, some swaps have virtually no effect. This could be represented as an "area of relevance" where only a certain region may change as a result of a swap. Since, as mentioned earlier, the size of each subarray in a possible swap is `1 << i`, the size of an area of relevance is `2 * (1 << i)`. When transitioning between indices, the bounds of the area of relevance will change: if the lower half of the area of significance overlaps with `[0, m]` after the current swap (or lack thereof) by exactly `1 << i`, the lower bound increases by `1 << i`, since all of the lower `1 << i` values will no longer change. Otherwise, the upper bound decreases by `1 << i` since all remaining upper values will not change. Eventually the area of relevance will converge onto an answer.
1295D|1800|AC|1|Understand that, if a number `b` is divisible by any combination of factors of `m` other than that of `gcd(a, m)`, `gcd(b, m)` will not equal `gcd(a, m)`. Using this, we can simply find the number of values divisible by `gcd(a, m)` in the range `[a, a + m)` that aren't divisible by any other remaining factors of `m` and since `m` can only have at most `11` factors, inclusion-exclusion principle with bitmasks may be used to find the this total.
1034A|1800|AC|3|Understand that any factor not already part of the `gcd` will do, so count how many times each prime factor and prime factor power is represented and whichever is closest to `n` without equaling `n` is the answer.
1560E|1800|AC|1|Understand that the order can be found by finding the order of occurences starting at the end of the string towards the beginning. This works because letters removed earlier will always have a final occurence before letters removed later. After this, simply simulating the removal of letters and checking it against the given string should be enough to validate the answer.
1316C|1800|AC|1|Understand that, given `x % p = 0` if `x` is divisible by p, `x * y % p != 0` if `x % p != 0` and `y % p != 0`. Since a coefficient of `h(x)` is represented as a sum of products of coefficients from `f(x)` and `g(x)` (with their respective powers of `x`), we can simply find a term in `h(x)` such that `a[i] * b[i] % p != 0` exists. Note that, when multiple such `a[i] * b[i]` are summed, it would require brute forcing to determine whether said sum still doesn't equal `0` modulo `p`. However, one way to ensure only a single `a[i] * b[i] % p != 0` is present is by finding the first term including one, which is as simple as finding the first `i` of `a` such that `a[i] % p != 0` and `j` of `b` where `b[i] % p != 0` and returning their sum.
1426E|1800|AC|4|Understand that one way to solve the minimum wins case is by maximizing the flow along non-winning edges. In my solution, however, I wanted to see if there was a less complicated approach and ended up looking at the editorial. They did not say why the solution works ("It can be shown..."); expect a better explanation in the future.
1466E|1800|AC|1|Understand that each bit contributes independently from other bits, so `and`-ing or `or`-ing an entire number is not required. Instead, the number of positive bits at a certain index could be totalled for all `a` and used to calculate the sum of all `and`s and `or`s for a given `a`. Summing the product of the `and` sum and `or` sum for each `a` yields the answer.
380C|2000|AC|2|Understand that the length of a maximum regular bracket subsequence could be greedily counted by subtracting the number of invalid open and closing brackets from the total length. This can be counted by going from left to right, adding `1` for each "(", subtracting `1` for each ")" and clamping the count to a value greater than `0`. Whenever the count needs to be clamped, that is an invalid ")" and in the end, if the count is greater than `0`, that is the number of invalid "(". With this in mind, we could find the counts at every index for every starting point of a substring of the original string and answer the queries that way. This could be done using a segment tree, updating per starting index. To count the indices that needed to be clamped, a fenwick tree could be used. (Note that this method is not the intended solution. The intended solution is much simpler, using a segment tree with a simple non-commutative combiner function. Let this be a reminder to self to practice segment trees/data structures in general.)
1438C|2000|AC|1|Understand that a checkered increasing of the cells would already fix initially same-number pairs. For pairs that become same-number, the checkers could be inverted, such that the neighbors it could pair with would also increase.
2B|2000|AC|4|Understand that dynamic programming for the minimum number of `2`'s or `5`'s yields an optimal solution, as only the minimum of the two yield the number of trailing zeroes.
1366D|2000|AC|2|Understand that splitting the set of factors into any two disjoint groups as `d1` and `d2` will always result in `gcd(d1 + d2, a) = 1`. This is because `d2 % d1 != 0`, since their factors are disjoint, so `(d2 + d1) % d1 != 0` as well. Since the sum is already not divisible by a factor of `a`, it cannot be divisible by `a` as a whole (the intended solution). Again, my actual solution deviated from the intended solution as I had realized that, all primes (starting with `5`) can be made by multiplying and adding smaller primes, at least until `19`, which is the largest `MEX` prime possible. For `2` and `3`, I just hoped that any combination of two other primes would suffice.
1370D|2000|AC|1|Understand that we can use a binary search to on the maximum of the smaller maximums. The checking function would be whether it's possible to arrange the values less than or equal to this maximum in an alternating pattern.
1359D|2000|AC|1|Understand that in every segment, Bob may only remove one card, a maximum card. Thus, for every card, we can assume it is the card Bob will take, and in return, no greater card may exist in the resulting segment (binary search). Then, using prefix sums and a range query data structure (segment tree), we can find the maximum sum among all possible segments.
1311D|2000|AC|2|Understand that the factors of any final `b` can be binary searched for such that their difference from `a` is minimum. For `c`, the greatest multiple of `b` smaller than `c` and the smallest multiple greater than `c` can both be calculated using math and then used to find a minimum difference.
1349B|2000|AC|8|Understand that a set containing `k` and `l` such that `l >= k` would only contain `k` after the operation. Also note that any set majority `k` would only contain `k` after the operation. With this in mind, we first want to make as many values as possible greater than or equal to `k`, which could be done using the second observation. Then, check if it is possible for the first case to happen, which would serve as a "seed" for the second case to finally fill the array.
1244C|2000|AC|5|Understand that the problem is essentially asking for a solution to `x * d + y * w = p (mod w)`, a Linear Diophantine Equation, which can easily be solved with the Extended Euclidean Algorithm. The solutions may also be shifted such that `x` and `y` are minimal such that their sum fits within `n`.
432D|2000|AC|1|Understand that a Z-function could be used to check how many suffix-prefix substrings exist at a certain index, since the value of the function at a certain index would correspond to the number of prefixes having substrings at said index. In addition, the Z-function could also be used to check whether a specific prefix is also a suffix.
242E|2000|AC|1|Understand that, while segment tree xor-ing entire values is quite difficult, processing each bit individually is pretty simple. A lazy segment tree supporting both range query and range update works here.
540C|2000|AC|4|Understand that, to fall through a cell, either the cell must be already cracked prior to visiting, or it must have a non-cracked neighbor to temporarily stay after cracking the target cell the first time.
1363E|2000|AC|1|Understand that the `k * a[u]` formula could be decomposed into `2 * a[u]` per swap in the subtree of node `u`. Note that descendants are inside the subtrees of their ancestors, so the cost of a descendant could be handled by an ancestor, thereby making the cost at any given node the minimum cost along its path to the root. With this, swaps could be solved greedily.
1288D|2000|AC|1|Understand that processing each `x` (with repeats), in decreasing order of value each `a[x][y]` only takes `O(N * M)` time. By storing a bitmask of visited `y` for each `x`, comparisons against other `x` that fulfill all `y` such that `a[x][y]` is the minimax only takes at most `O(2 ^ M)`.
1132F|2000|DNF|0|N/A
1354C2|2000|AC|1|Understand that, on `[0, PI / n)`, the width (the initially larger dimension) of the `2n-gon` is monotonically decreasing, and the height (initially smaller) is monotonically increasing. Combined with the fact that, in order to minimize the maximum, both dimensions should be close as possible to each other, otherwise the larger dimension can be decreased or the smaller increased. Thus, a binary search on their difference (also monotonic as a result of the first observation) towards `0` should yield the optimal answer.
1200E|2000|AC|3|Understand that Knuth-Morris-Pratt can be used to determine by how much the two strings may overlap by running the function on a string `b + "/" + a` where `b` is the word to be added and `a` is the existing word.
514C|2000|AC|1|Understand that the maximum number of operations during queries given the problem restraints is (very roughly) `1e8` using a trie, this could be found using a separate program with `i + 2 * i * (i + 1) / 2` as the number of trie nodes given `i` as the length of all input and query strings, `3 * i + 1` as the number of strings required to fill such a tree and `i * (3 * i + 1)` as the total length.
1416B|2000|AC|2|Understand that, loading the first index with all values, then distributing the values among the remaining indices such that no index goes negative produces a solution with exactly `3n` operations. To do this, for each `0`-indexed `i` from `[1, n)`, lend `-a[i] (mod i + 1)` to `a[i]` to initially make it a multiple of `i + 1`, then transfer the entire `a[i]` back to `a[0]`. This works because `a[i] >= 1`, meaning that, at every index, `a[0]` stands to increase by at least `1`, making it possible to handle any modulo if processed in increasing order: `a[0] >= 1` at index `1` where modulo is `[0, 1]`, `a[0] >= 2` at index `2` where modulo is `[0, 2]`, etc.
1399E1|2000|AC|2|Understand that each edge, when divided by `2` decreases the total path sum by a certain amount, the effect of which decreases per division. The problem can be solved greedily by running a priority queue for maximum decreases.
1268B|2000|AC|4|Understand that a tiling can be achieved if there is a perfect pairing between every black cell and every white cell, assuming a checkerboard coloring. Meaning, the result is simply the minimum of the number of black cells and the number of white cells. See "domino tiling problem" for further analysis.
1359E|2000|AC|1|Understand that, as long as the `gcd` of all the numbers in `a` is included in `a`, the array is stable. Using combinatorics, the number of possible arrays of length `k` for each `gcd` can be summed to produce an answer.
1674E|2000|AC|3|Understand that there are four simple ways to get a minimum answer. The first is only shooting adjacent pairs of walls. This works because both walls contribute to each other's breaking as neighbors. The second is only shooting the two weakest walls. The third is shooting a wall with the goal of breaking its neighbors. The fourth and final method is similar to the third, but shooting the stronger of the two neighbors as well.
383C|2000|AC|1|Understand that simply keeping track of the odd-depth and even-depth nodes and storing their data in separate segment trees, updating them using their respective Euler tour ranges is enough to differentiate even and odd children of a node.
1427C|2000|AC|4|Understand that the maximum distance between celebrities is `2 * (r - 1)`. Therefore any celebrities arriving in `2 * (r - 1)` minutes or greater in the future will always be reachable and only those outside this range need to be explicitly checked against. With this in mind, at most `O(R * N)` operations need to be done.
478D|2000|AC|2|Understand that the maximum `h` among all possible `r` and `g` is `893`. Knapsack DP can produce a result in roughly `O(H * R)`, worst case.
1156C|2000|AC|1|Understand that a matching can be created between the bottom `m` values and top `m` values. Binary searching for this value `m` produces an answer.
337D|2000|AC|1|Understand that DP on trees can be used to find the maximum distance to an affected settlement. For every node whose maximum distance to an affected settlement is less than or equal to `d`, it is possible the settlement contains the Book of Evil.
920F|2000|AC|2|Understand that each `a` can change at most `6` times before replacements no longer affect it, meaning that the array will not change after at most `N * 6` operations. For this, we can keep a set of all `i` such that the `a[i]`, as it is currently, will change after an operation, and update only such `i` in range `[l, r]` for all replace operations. Sum operations can be handled using any point update range query data structure. If Fenwick tree is used, the final complexity is `O(N * log(N))`.
1415D|2000|AC|1|Understand that if the number of leading zeroes of more than two consecutive `a` are equal, the last two can be xor'ed, resulting in a non-non-decreasing array. Otherwise, `n` is at most `60`, meaning we can brute force all number of operations on the left-hand side and right-hand side of all possible "border"s where a border describes the position at which `a[i] < a[i + 1]`.
359D|2000|AC|1|Understand that an `a[i]` divides all `a[j]` such that `l <= i, j <= r` if `gcd(a[j])` for all such `j` equals `a[i]`. We can find, for all such `a[i]`, `l` and `r` using binary search and a range query data structure like sparse table.
1304E|2000|AC|1|Understand that we can use Euler tour and binary lifting to calculate the least common ancestor of any two nodes to then find the distance between them. This can be used to test all possible paths betwen `a` and `b` in each query: `a` to `x` to `y` to `b`, `a` to `y` to `x` to `b`, and `a` to `b`. If any of these path lengths have the same parity as `k` and are less than or equal to `k`, edges can be added to the path to reach such a length.
451D|2000|AC|3|Understand that, with regards to bounds, any `a` can be paired with any `a` before it and any `b` can be paired with any `b` before it, so keeping prefix sums of `a`'s and `b`'s can allow us to count the number of good substrings using combinatorics. If an index is of odd distance to its partner, their resulting substring must be of even length, otherwise it is odd.
466B|2000|AC|2|Understand that, assuming `b1` always equals `(6 * n + a1 - 1) / a1`, the requirements are always satisfied for positive `a1`. In addition, for all values `a1` less than or equal to `f = floor(sqrt(6 * n - 1)) + 1`, values of `b1` greater than or equal to `f` will be tested. This results in all relevant values satisfying the stated requirements being tested.
1380D|2000|AC|4|Understand that we can, first, find all removed ranges (and print "-1" if deemed invalid in this stage), and determine the minimum cost of removing such a range. If `x >= k * y`, then as many operations of the second type should be used. This can be accomplished in two cases: with `len` as the length of the range, if `len >= k`, by using the warrior of greatest power within the range to destroy other warriors until there are at most `k` warriors remaining, we can destroy the rest of the warriors using the first operation if the warriors cannot be entirely destroyed using either of the boundary warriors and with the second operation otherwise. If `len < k`, all warriors in the range must be destroy-able using either of the boundary warriors, or the transformation is impossible. If `x < k * y`, using the most powerful warrior to destroy warriors until the number of remaining warriors is divisible by `k` and destroying the rest using the first operation is ideal.
1536D|2000|AC|1|Understand that, for every two elements added, the median can only shift at most one index. This allows us to create a constructive algorithm that, upon seeing a new median, attributes its value to coming from one of the two elements added. Remaining elements can be either `-10 ^ 9` or `10 ^ 9` depending on constraints. This allows us to determine the existence of an array `a` based on whether medians can be added without "overstepping" previously added medians, since such medians need to be visited first before seeing the current one.
1493C|2000|AC|2|Understand that you can binary search for the least significant letter that would need to be updated to produce a satisfactory string, then brute force for the letter it would be updated to.
1567D|2000|AC|10|Understand that a solution can be greedily constructed where, if it is possible to "split a digit" (e.g. `900` to `800` and `100`), it should always be done. Otherwise, the least significant digit must be "decomposed" (e.g. `100` to ten `10`s). This always produces the optimal solution as splitting a digit has `0` cost and decomposing a digit has cost equivalent to the digit in base `11` and this should always be as insignificant as possible.
1521C|2000|AC|1|Understand that, when cases for `p[i]` and `p[j]`, in relation to `x`, are laid out, it is clear that in some cases, the maximum or minimum of `p[i]` and `p[j]` can be found. Combine this with the fact that the `p[i]` for some index `i` can be found in two queries, the remaining numbers can be found using the aforementioned minimum/maximum property. In addition, if the initial `p[i]` is greater than half, the minimum property should be used, as at least half of all `p[j]` can be found using such a query. Similar case for `p[i]` being less than half, using the maximum property instead. This ensures that the total number of queries will be less than `floor(3 * n / 2) + 30`.
1632D|2000|AC|1|Understand that the left bound `l` for each index `r` can be found using binary search, as `gcd(l, r)` monotonically decreases and `r - l + 1` monotonically increases as `l` decreases. Then, operations can be performed greedily, processing the indices in increasing order, choosing the maximum index possible for an operation each time if needed. It can be shown this produces an optimal result.
1634D|2000|AC|2|Understand that given three numbers, `x`, `m` and `y`, where `x` and `y` represent the extremes of the three numbers, we can determine if a number `z` is more extreme in the `x` or `y` direction by substituting them for `x` and `y` respectively and taking the maximum of their query results. Whichever direction `z` is more extreme in should then be replaced with `z`. Once all checks are complete, the two most extreme values should be provided in the answer, as `0` itself is an extreme value (no value can go below `0` according to the statement). The initial values of `x`, `m` and `y` can be found in `4` queries in the beginning, then subsequent checks for `z` can be found in `(n - 4) * 2` queries for a total of `2 * n - 4` queries.
1451E1|2000|AC|1|Understand that `a[0]` can be found using `AND 0 1` (`0`-indexed for the sake of consistency), `OR 0 1`, `AND 0 2`, `OR 0 2` and `AND 1 2`. This is because, for all bits where `AND 0 1` or `AND 0 2` are `1`, `a[0]` must be `1` and, for all bits where `OR 0 1` and `OR 0 2` are `0`, `a[0]` must be `0`. All remaining bits `i` can either be as a result of `{1, 0, 0}` or `{0, 1, 1}`, where `{x, y, z}` represents bit `i` of `a[0]`, `a[1]` and `a[2]`, respectively. Finally, all other `a[k]` can be found using `XOR 0 k`.
578C|2000|AC|1|Understand that we can binary search for the optimal `x`. Since the minimal negative subsegment value and maximum positive subsegment value both contribute to the maximum absolute subsegment value, we can binary search to make them as close to equal as possible. The maximum or minimum subsegment of an array can be found in linear time.
475D|2000|AC|1|Understand that a number `a` can have up to `log2(a)` unique `gcd` subsegment values. This is because each additional unique `gcd` is the result of removing at most one prime factor and the smallest prime factor, `2`, can fit `log2(a)` times in `a`.
1804D|2000|AC|8|Stupid greedy. Will explain later or, better yet, solve it properly.
961D|2000|AC|11|Understand that each point must be part of at least one line segment. This means that, for a point `x`, we can sort all other points by their slope relative to `x` and call a single group of points with identical such slope a line. This is done twice and, if there are still points unattached to either of the previous lines, the answer is `NO`.
52C|2200|AC|1|Understand that it's just range update range query but cyclical if `l > r`.
617E|2200|AC|3|Understand that a modified Mo's algorithm can handle the range queries in `O(N * sqrt(N))`. Instead of walking the left bound, we re-calculate it each time as the set of xor prefix pairs may be different for each right bound.
570D|2200|AC|7|Understand that Euler tour can be used to find children of nodes. This can be used to find the children of a node at a certain depth, and furthermore, of a certain letter. If there is no more than one letter of odd count for a query, the answer is `YES`.
559C|2200|AC|2|Understand that PIE can be used to find the number of ways to the bottom right corner from each black cell, and then the number of ways from the top left corner.
165E|2200|AC|3|Understand that a number `a` is compatible with `b` if `a | ~b = ~b`, where `~x` denotes `x ^ ((1 << 14) - 1)`. We can find such an `a | ~b` using bitmask dynamic programming, where, starting with an `a`, we can set bits making all `a | x` possible, where `x` is in range `[0, 1 << 14)`.
1485D|2200|AC|1|Understand that the `gcd` of all numbers `[1, 16]` is `720720`, which all numbers `[1, 16]` can differ by a `k ^ 4`. Arranging `720720` and such numbers in a checkerboard pattern ensures a solution.
1400E|2200|AC|6|Understand that we can use dynamic programming, storing for the number of operations of the first kind being done on the current index.
1537E2|2200|AC|3|Understand that we can use a Z-function to find the first postition in `s` where each prefix would be different if repeated to fit and determine if said prefix is lexicographically greater or lesser than the original string. If it is strictly lesser, repeat this prefix and trim to size `k`.
1407D|2200|AC|8|Understand that a monotonically increasing and decreasing stack can be used to describe all skyscrapers that can be jumped from at each index.
1438D|2200|AC|1|Understand that the `xor` of all elements always remains the same. This is because for each operation containing `a[i]`, `a[j]` and `a[k]`, just focusing on `a[i]`, it contributes `a[i]`, `a[i] ^ a[j]` and `a[i] ^ a[k]`, meaning the net `xor` difference is `0`. The same can be said for `a[j]` and `a[k]`. With this, we can determine that if the array has even length and an `xor` other than `0`, it is impossible to make all elements equal. Otherwise, `xor`ing three consecutive elements every two elements produces a number of even-sized groups of equal elements and one odd-sized group of equal elements. Each even-sized group can be made equal to an element in the odd-sized group by `xor`ing a pair of elements from the even-sized group with one from the odd-sized group. This results in `n - 2` operations.
1333F|2200|AC|1|Understand that all `gcd`s `x` have a list of "dependencies" or values that, when `gcd`ed result in `x`. With this, we can process the `gcd`'s in decreasing order, getting rid of un-deleted dependencies as we go. The result for the current number of un-deleted dependencies is the `gcd`'s value minus one.
1092D1|2200|DNF|0|Marked DNF because I did not solve this problem myself.
1474D|2200|AC|3|N/A
11D|2200|AC|1|N/A
833B|2200|AC|1|N/A
1110E|2200|AC|2|N/A
903D|2200|AC|3|N/A
1467D|2200|AC|1|N/A
1428E|2200|AC|6|N/A
1470D|2200|AC|2|N/A
13C|2200|AC|2|N/A
551C|2200|AC|2|N/A
1406D|2200|AC|1|N/A
1567E|2200|AC|2|N/A
1520G|2200|AC|2|N/A
7D|2200|AC|1|N/A
1437E|2200|AC|1|N/A
1336C|2200|AC|1|N/A
1156D|2200|AC|1|N/A
1110D|2200|AC|2|N/A
1515E|2200|AC|1|N/A
915D|2200|AC|2|N/A
282E|2200|AC|2|N/A
1389E|2200|AC|1|N/A
1656E|2200|AC|1|N/A
1503C|2200|AC|1|N/A
1327D|2200|AC|2|N/A
1353F|2200|AC|1|N/A
280C|2200|AC|2|N/A
1328F|2200|AC|3|N/A
1338C|2200|AC|2|N/A
1305E|2200|AC|2|N/A
1175E|2200|AC|3|N/A
1520F2|2200|AC|7|N/A
1215E|2200|AC|2|N/A
1630C|2200|AC|2|N/A
1486E|2200|AC|1|N/A
1373E|2200|AC|3|N/A
1092D2|2200|AC|1|N/A
1114E|2200|AC|2|N/A
1552F|2200|AC|1|N/A
839D|2200|AC|1|N/A
1037E|2200|AC|2|N/A
1238E|2200|AC|1|N/A
768D|2200|AC|1|N/A
1334E|2200|AC|2|N/A
1154G|2200|AC|3|N/A
1253E|2200|AC|6|N/A
1303E|2200|AC|1|N/A
707D|2200|AC|6|N/A
1535E|2200|AC|2|N/A
1059D|2200|AC|4|N/A
1556E|2200|AC|3|N/A
1730D|2200|AC|2|N/A
1542D|2200|AC|1|N/A
1097D|2200|AC|4|Understand that the probability of any given path is the product of the inverse of the number of times each prime occurs in the prime factorization of each number along that path. Instead of combining based on number, since there are many possible numbers along the path from one number to another, we can combine based on prime, as the sum of the probabilities of the ways to transition from one prime count down to another can be efficiently calculated using dynamic programming and combining them is as simple as multiplying their sum.
590C|2200|AC|3|N/A
1384B2|2200|AC|1|N/A
1156E|2200|AC|1|N/A
1415E|2200|AC|1|N/A
429D|2200|DNF|0|N/A
616E|2200|AC|6|N/A
1557D|2200|AC|3|N/A
1220E|2200|AC|3|N/A
549G|2200|AC|1|N/A
505D|2200|AC|4|N/A
547A|2200|AC|11|N/A
1526D|2200|AC|4|N/A
1616E|2200|AC|1|N/A
1806E|2200|AC|8|N/A
592D|2200|AC|1|N/A
1537F|2200|AC|2|N/A
1295E|2200|AC|1|N/A
1736D|2200|AC|2|N/A
27D|2200|AC|2|N/A
1717E|2200|AC|1|N/A
1498D|2200|AC|3|N/A
1234F|2200|AC|1|N/A
1641C|2200|AC|3|N/A
908D|2200|AC|1|N/A
1100E|2200|AC|1|N/A
1788E|2200|AC|1|N/A
1168C|2200|AC|2|N/A
438D|2300|AC|3|N/A
558E|2300|AC|3|N/A
786B|2300|AC|1|N/A
1009F|2300|AC|3|N/A
1188B|2300|AC|1|N/A
713C|2300|AC|4|N/A
598C|2300|AC|4|N/A
915E|2300|AC|2|N/A
1450C2|2300|AC|3|N/A
718C|2300|AC|2|N/A
1628C|2300|AC|2|N/A
451E|2300|AC|2|N/A
1699D|2300|AC|3|N/A
383D|2300|AC|1|N/A
1451E2|2300|AC|1|N/A
1198D|2300|AC|1|N/A
708C|2300|AC|2|N/A
1342E|2300|AC|1|N/A
547C|2300|AC|1|N/A
1422D|2300|AC|2|N/A
715B|2300|AC|5|N/A
675E|2300|AC|2|N/A
154C|2300|AC|1|N/A
1495C|2300|AC|2|N/A
1494D|2300|AC|4|N/A
785D|2300|AC|1|N/A
1203F2|2300|AC|1|N/A
1182E|2300|AC|2|N/A
1404C|2300|AC|1|N/A
1528C|2300|AC|2|N/A
543D|2300|AC|2|N/A
1540B|2300|AC|1|N/A
1396C|2300|AC|1|N/A
1228E|2300|AC|2|N/A
487C|2300|AC|2|N/A
1371E2|2300|AC|1|N/A
1536E|2300|AC|1|N/A
1658D2|2300|AC|1|N/A
1824B2|2300|DNF|0|N/A
1693C|2300|AC|11|N/A
1408F|2300|AC|1|N/A
160D|2300|AC|2|N/A
1073E|2300|AC|1|N/A
1385F|2300|AC|2|N/A
808G|2300|AC|2|N/A
817F|2300|AC|3|N/A
1270E|2300|AC|4|N/A
1706E|2300|AC|1|N/A
1592D|2300|AC|2|N/A
510E|2300|AC|1|N/A
1553F|2300|AC|1|N/A
891C|2300|AC|2|N/A
1614D2|2300|AC|1|N/A
732F|2300|AC|1|N/A
1282D|2300|AC|5|N/A
623B|2300|AC|3|N/A
515E|2300|AC|1|N/A
788C|2300|AC|2|N/A
1712E1|2300|AC|1|N/A
1322C|2300|AC|2|N/A
1251E1|2300|AC|2|N/A
1251E2|2400|AC|1|N/A
149E|2300|AC|3|N/A
1453E|2300|AC|2|N/A
1139D|2300|AC|1|N/A
1603C|2300|AC|1|N/A
1625D|2300|DNF|0|N/A
1783E|2300|AC|1|N/A
1654E|2300|AC|2|N/A
884D|2300|AC|2|N/A
1607F|2300|AC|6|N/A
1705E|2300|AC|1|N/A
1380E|2300|AC|1|N/A
1292C|2300|DNF|0|N/A
1695D2|2300|AC|4|N/A
1601C|2300|AC|2|N/A
1132D|2300|AC|1|N/A
1550D|2300|AC|1|N/A
652E|2300|AC|4|N/A
85D|2300|AC|1|N/A
1534E|2300|AC|9|N/A
1394B|2300|AC|2|N/A
570E|2300|DNF|0|N/A
1093G|2300|AC|2|N/A
1552E|2300|AC|2|N/A
1190C|2300|AC|1|N/A
808E|2300|AC|7|N/A
594A|2300|AC|1|N/A
1621E|2300|AC|3|N/A
1834E|2300|AC|1|N/A
1768E|2300|DNF|0|N/A
1691E|2300|AC|1|N/A
1236D|2300|AC|2|N/A
1245F|2300|AC|1|N/A
1148E|2300|AC|1|N/A
960E|2300|AC|3|N/A
1196F|2200|DNF|0|N/A
1070A|2200|DNF|0|N/A
1646E|2200|DNF|0|N/A
1399E2|2200|DNF|0|N/A
653D|2200|DNF|0|N/A
1398E|2200|DNF|0|N/A
1477C|2200|DNF|0|N/A
1704E|2200|DNF|0|N/A
679B|2200|DNF|0|N/A
813E|2200|DNF|0|N/A
1583E|2200|DNF|0|N/A
1034B|2200|DNF|0|N/A
301D|2200|DNF|0|N/A
1579G|2200|DNF|0|N/A
1562D2|2200|DNF|0|N/A
1840G1|2200|DNF|0|N/A
1635E|2200|DNF|0|N/A
1461E|2200|DNF|0|N/A
1311E|2200|DNF|0|N/A
427D|2200|DNF|0|N/A
402E|2200|DNF|0|N/A
1158B|2200|DNF|0|N/A
56E|2200|DNF|0|N/A