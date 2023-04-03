# Practice Problems Status
Problem|Rating|Correct cases|Attempts|Notes
-|-|-|-|-
1105C|1500|AC|1|N/A
1674B|800|AC|1|N/A
1499A|800|AC|1|N/A
1581A|800|AC|1|N/A
629A|800|AC|1|N/A
1543B|900|AC|1|N/A
1582B|900|AC|1|N/A
1166A|900|AC|1|N/A
1293B|1000|AC|1|N/A
1539A|1000|AC|1|N/A
610A|1000|AC|1|N/A
1732A|1000|AC|2|N/A
535B|1100|AC|1|N/A
630C|1100|DNF|1|N/A
1743A|800|AC|1|N/A
1305C|1600|AC|4|N/A
1539A|1000|AC|2|N/A
1475E|1600|AC|1|Understand that all values except those interchangeable with the "border" are fixed, and that the combinations of the aforementioned values can be trivially calculated for.
322B|1600|AC|2|Solution could have been more exact, went with brute forcing for all possible remainders and maximizing each case.
1284C|1600|AC|1|Understand that combinations for each segment length can be trivially calculated for. I feel like I'd classify this as a "classic" combinatorics problem based on the 3 major ones I've done so far as they kind of work me into this specific mindset and approach.
735C|1600|AC|2|Fibonacci sequence; understand the tree-like structure and how it relates to the structure of the fibonacci sequence.
364A|1600|AC|4|Understand that the dimensions of the rectangle can be separated such that their relation can be solved in constant time.
340C|1600|AC|1|Another "classic" combinatorics problem. Understand that each pair occurs `(n - 1)! * 2!` times, and each `a` is a "beginning" `(n - 1)!` times. Meanwhile, the number of total permutations is `n!`. Since `(n - 1)!` will always be a factor of both the numerator and denominator, we don't even need to process it for either. Then factor out the `gcd` of both.
319A|1600|AC|1|Understand that the only time `a < b && (a ^ x) > (b ^ x)` holds true is when `a` and `b`'s first different bit lies on a `1` on `x` at the same index. The thought process began with recognizing that `a == b && (a ^ x) == (b ^ x)` would remain equal until their first different bit, which led me to realize that it's the first different bit that determines whether or not the inequality is satisfied.
272D|1600|AC|2|Understand that, since the second value does not matter in the ordering, any order of the second value is possible as long as the first remains non-decreasing. However repeats may happen when there are multiple of a certain pair, namely at most two since each second value may occur at most twice. Therefore we can multiply all possible orderings of each "chunk" and divide for duplicates by simply removing all `2`'s from the factorials and multiplying them manually to handle non-prime modulos.
630G|1600|AC|1|Understand that you can either place a pennant, or move to the next table. As long as all penants are placed and all tables are visited, the combination is valid. Thus, we there are `bin(n - 1 + x, x)` combinations for `n` tables and `x` penants.
52B|1600|AC|1|Understand that all triangles have a horizontal and vertical side, and thus, a point containing both the horizontal and vertical components of those sides: the right-angle corner. Using this, we can use combinatorics to combine for the other two corners.
323A|1600|AC|1|Understand that, for a single-colored group to consist of only cubes with exactly two neighbors of the same color, the group must behave like a cycle such that a cube is neighbor to a "previous" cube and a "next" cube, and the last cube's "next" is the first cube. With this in mind, due to the Euclidean nature of the space, there can only be an even number of cubes to a group. Thus, cubes of odd numbers are always impossible to fill. Even numbers, on the other hand, can be tiled using 2x2x2 cubes consisting of a 1x2x2 white layer and a 1x2x2 black layer.
1301C|1700|AC|2|Understand that each "gap" consisting of only `0`'s subtracts `x * (x + 1) / 2` substrings from the answer, where `x` is the length of the "gap". Thus, this becomes a greedy problem of distributing the non-`1` characters among gaps such that the final cost is minimum.
1312D|1700|AC|1|Understand that `n - 1` unique numbers are selected from numbers `[1, m]` for each array. Now it's a matter of distributing them among the left and right sides of the "peak". For this, we can go through all possible sizes of the left side, where we choose `i` values from the `n - 2` non-"peak" chosen numbers to be on the left, while the rest go to the right. Then, we can choose one of those `i` values to be the duplicate on the right side.
1699C|1700|AC|1|Understand that, for a subarray to have a certain MEX, it must contain every value below the MEX but not the MEX itself. Combined with the fact that the complete array is a permutation, every MEX greater than `0` has at most one subarray, and that subarrays from previous MEXs are contained within it. For the subarray of each MEX, any order of values are possible as long as the value one below the MEX is on the edge of the subarray such that without it, the subarray would not have this MEX, and the subarrays contained within it also satisfy the problem.
1598D|1700|AC|2|Understand that for a combination of 3 to be invalid, both conditions must not be satisfied. Note that each pair is unique, therefore in a combination of 3, there must be one pair where both values are duplicates, one pair where only the first is a duplicate and one where only the second is. This makes it easy to find invalid combinations by going through all possible pairs of the first type, as well as possible second and third types for those first types.
1715|1700|AC|1|Understand that there is at most one "split" between each adjacent pair, and that each split contributes to `l * r` subarrays, where `l` is the number of blocks to the left of the split and `r` is the number of blocks to the right.
1329B|1700|AC|1|Understand that the only way a `b < b ^ a` is if `a`'s leading bit is greater than `b`'s leading bit.
621C|1700|AC|2|Understand that each pair of cyclically adjacent sharks contribute to the expected count independently.
1102E|1700|AC|2|Find all strongly connected components, the answer is `2 ^ (n - 1)`, where `n` is the number of components. The reason is that each node in a strongly connected component has to have the same value. Meanwhile, each next strongly connected component can be at most one more than the previous, allowing `2 ^ (n - 1)` different combinations as the first component always has to equal `0`.
1043D|1700|AC|1|Find all valid common parts. Combinations can be found easily by length.
1735D|1700|AC|1|Understand that, in order to make a meta-set of five containing multiple sets of three following the criteria, the overlap between the sets must equal exactly `1`. If there was an overlap of two, since two cards enforce a single unique third card, the set would ultimately overlap with itself, which does not contribute to the meta-set. If it was any less, the sum of the cards would not be 5.
689C|1700|AC|1|Binary search for `n`. For all values of `k`, total the number of ways for each `n` and compare with the target `m`.
327C|1700|AC|1|Understand that there are `(2 ** 0) * m + (2 ** 1) * m +  + (2 ** 2) * m + ... + (2 ** (k - 1)) * m` ways to produce a magic number, where `m` is the number of ways to produce a magic number in a single copy of `a`. This can't be computed naively because `k` is too big, therefore an approach similar to the modulo exponent function can be used.
596C|1700|DNF|0|N/A
929C|1700|DNF|0|N/A
300C|1800|AC|1|Understand that each distribution of `a`'s and `b`'s have the same sum as long as the number of `a`'s and the number of `b`'s are equal. We can use `bin(n, i)` to find the number of numbers such that the number of `a`'s equals `i`.
1420D|1800|AC|2|Understand that each lamp can pick `k - 1` other lamps to open the door. Therefore, we can, for each lamp, find how many other lamps overlap with its beginning time and choose `k - 1` of them. Note that multiple lamps may begin at the same time and thus, need to be removed once processed.
1552C|1800|DNF|0|N/A
1207D|1800|DNF|0|N/A
1705D|1800|DNF|0|N/A
1195D2|1800|DNF|0|N/A
986B|1800|DNF|0|N/A
894B|1800|DNF|0|N/A
1750D|1800|DNF|0|N/A
1442B|1800|DNF|0|N/A
1508B|1800|DNF|0|N/A
991E|1800|DNF|0|N/A
652C|1800|DNF|0|N/A
603B|1800|DNF|0|N/A
690D2|1800|DNF|0|N/A
1400D|1900|DNF|0|N/A
459C|1900|DNF|0|N/A
1444B|1900|DNF|0|N/A
1238D|1900|DNF|0|N/A
1545B|1900|DNF|0|N/A
1371E1|1900|DNF|0|N/A
1202D|1900|DNF|0|N/A
552D|1900|DNF|0|N/A
1717D|1900|DNF|0|N/A
1172B|1900|DNF|0|N/A
1000D|1900|DNF|0|N/A
