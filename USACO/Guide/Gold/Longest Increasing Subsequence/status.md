# Practice Problems Status
Problem|Rating|Correct cases|Attempts|Notes
-|-|-|-|-
PCB|Normal|AC|1|N/A
Increasing Subsequence|Easy|AC|3|N/A
Consecutive Subsequence|Easy|AC|1|N/A
LCS on Permutations|Normal|AC|1|N/A
Cowjog|Normal|AC|1|N/A
Rabbit Carrot|Normal|AC|1|N/A
Korney Korneevich and XOR|Normal|AC|2|N/A
2009 - Candy|Hard|AC|3|Understand that the minimum number of wagons required to catch all the candies is equal to the size of the maximimal set of candies such that no two candies in the set are reachable in time. To find this set, we can imagine the "infinite triangle of reachability" that every candy has if the wagon is at that candy. Since no two candies in the set should be reachable from each other, no candy in this set can be in another candy's triangle. Now, say we already found such a set. If you draw out all the triangles and rotate the drawing $45 \degree$, the positions of the corners appear to be increasing! Meaning that, if we find the longest increasing subsequence of the points rotated $45 \degree$, we get the minimum number of wagons required. To assign wagons to candies, first note that the path of every wagon is always non-decreasing along the drawing. This means that points higher up should be assigned wagons higher up, which can be done using binary search.
2018 - Global Warming|Hard|AC|2|N/A
2016 - Matryoshka|Hard|AC|2|Understand that the number of towers is equivalent to the size of the maximum set of dolls that cannot fit inside each other. If we visualize this, it appears that all such sets are decreasing subsequences, meaning the maximum such set is a longest decreasing subsequence. We can answer the queries as we process the dolls in increasing order of height, and use binary search to find the current longest decreasing subsequence ending in a doll of diameter greater than or equal to $a$. This works since all stored states represent the greatest number that a decreasing subsequence of corresponding length can end with.