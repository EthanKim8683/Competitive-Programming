# Practice Problems Status
Problem|Rating|Correct cases|Attempts|Notes
-|-|-|-|-
339D|1700|AC|2|Understand that the data may follow a segment tree-like structure, where each update only takes `O(N)` operations to do. 
1359C|1700|AC|1|Understand that each odd iteration of the procedure deviates from `(h + c) / 2` less and less, and since `h` is always positive, the function is monotonically decreasing. This means binary search may be used to find the most optimal solution.
478C|1800|DNF|0|N/A
448D|1800|AC|1|Understand that the number of table values less than `x` can be calculated in `O(N)` by summing up, for each `i` from `1` to `n` inclusive, how many multiples of `i` are less than `x`. This can be binary searched for in `O(log(N * M) * N)` time by comparing the number of table values less than `x` to `k - 1`.
1396B|1800|AC|1|Understand that a greedy approach may be proven. Assuming `s` equals the number of stones, if the first player chooses the pile with more than `floor(s / 2)` stones, they would win. This is because the second player would run out of stones before the first, being forced to choose from the smaller half of the stones. Now, if there are no piles with more than `floor(s / 2)` stones, then there are two cases: if `s` is even, a perfect matching can be applied such that each stone in one pile is matched with another stone in another pile. This would always result in the first player losing because, if the first player makes a move, the second player can always choose the matched stone. If `s` is odd, however, the "even" case is reversed, where the second player makes a move and the first player always chooses the matched stone, resulting in the first player winning.
1355C|1800|AC|1|Understand that, once the largest side `z` has been determined, the only way `x` and `y` can be chosen such that the resulting triangle is degenerate is if `x` and `y` total less than `z + 1`. This forms inequality `x + y >= z + 1`, which, combined with all other constraints on `x` and `y`, could be solved for all possible `z` in `O(D)` time. Note that a graphical approach would be tricky here; it would be more sensible to simply solve for the inequalities mathematically.
1388C|1800|AC|1|Understand that the correctness of the collected happiness indexes can be solved independently for each city. Simply checking if there are no relative increases in happiness from parent to child and if the happiness of a city is valid yields the correct answer.
1326D2|1800|AC|2|Understand that, we can greedily find the largest same-length prefix and suffix of `s`, then find the longest palindrome prefix or suffix in the remaining middle section. The reason this works is because, for every character given to the prefix/suffix length, at most one pair of characters is taken away from the middle palindrome, resulting in a net difference of at least `0`. To find the longest palindrome prefix or suffix, Knuth-Morris-Pratt can applied to the middle section. However, naively finding the maximum proper prefix of such a string would not work, as a proper prefix cannot equal the string itself. A workaround would be to concatenate the string, followed by a delimeter and ending with the string reversed. This way, an entire prefix palindrome would match with itself as a prefix of the initial string and a suffix of the reversed string.
1329A|1800|DNF|0|N/A
459D|1800|DNF|0|N/A
|1800|DNF|0|N/A
|1800|DNF|0|N/A
|1800|DNF|0|N/A
|1800|DNF|0|N/A
|1800|DNF|0|N/A
|1800|DNF|0|N/A
|1800|DNF|0|N/A
|1800|DNF|0|N/A
|1800|DNF|0|N/A
|1800|DNF|0|N/A
|1800|DNF|0|N/A
|1800|DNF|0|N/A