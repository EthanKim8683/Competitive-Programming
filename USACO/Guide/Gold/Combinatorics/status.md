# Practice Problems Status
Problem|Rating|Correct cases|Attempts|Notes
-|-|-|-|-
Binomial Coefficients|Easy|AC|1|N/A
Montmort Numbers|Easy|AC|1|Understand that dynamic programming can be used, since we can either replace any existing `p` from a valid permutation with the latest `p` or we can replace an invalid `p` in a permutation with one invalid `p` with the latest `p` to get the current number of valid permutations.
Creating Strings II|Easy|AC|1|N/A
Distributing Apples|Easy|AC|1|N/A
Christmas Party|Easy|AC|1|N/A
Infinite Replacement|Easy|AC|1|N/A
Close Tuples|Easy|AC|3|N/A
Almost Identity Permutations|Normal|AC|1|N/A
Just Stalling|Easy|AC|1|N/A
Bots|Normal|AC|1|N/A
Strivore|Normal|AC|1|Understand that between two letters `s[i]` and `s[i + 1]` in `s`, all inserted letters must not equal `s[i + 1]` because if some position `j` between `i` and `i + 1` in the transformed string `t` satisfied `t[j] == s[i + 1]`, then in a different string `s[i + 1]` could be located at `j` while another letter equivalent to `s[i + 1]` could exist at `i + 1`. This would result in double counting.
Moo Route|Normal|AC|1|Understand that the problem can be visualized as alternating $\textit{left}$ and $\textit{right}$'s (starting with $\textit{right}$ and ending with $\textit{left}$) and, at every $i$ such that $A _ i > A _ {i - 1}$, we can insert an adjacent $\textit{left} / \textit{right}$ pair $\frac{A _ i - A _ {i - 1}}{2}$ times. Similarly, at every $i$ such that $A _ i < A _ {i - 1}$, we remove $\frac{A _ {i - 1} - A _ i}{2}$ adjacent $\textit{right} / \textit{left}$ pairs. Mathematically, we can represent the number of ways to handle the aforementioned cases as $\dbinom{\frac{A _ {i - 1} - 2}{2} + \frac{A _ i - A _ {i - 1}}{2}}{\frac{A _ i - A _ {i - 1}}{2}}$ for the insertions (stars-and-bars) and $\dbinom{\frac{A _ {i - 1}}{2}}{\frac{A _ {i - 1} - A _ i}{2}}$ for the removals. If it helps, one can draw a picture to see why this works.
Cowpatibility|Normal|AC|1|N/A
Arena|Normal|AC|3|N/A
Help Yourself|Normal|AC|1|For each segment, we can either introduce a new connected region, or extend an existing one. To introduce a new connected region, transition from all unions ending before the current segment. To extend an existing one, transition from all unions ending after the current segment.
Fancy Stack|Hard|AC|2|N/A