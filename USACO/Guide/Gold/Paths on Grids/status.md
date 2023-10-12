# Practice Problems Status
Problem|Rating|Correct cases|Attempts|Notes
-|-|-|-|-
Grid Paths|Easy|AC|2|N/A
Longest Common Subsequence|Easy|AC|1|N/A
Edit Distance|Easy|AC|1|N/A
Cow Checklist|Easy|AC|3|N/A
Radio Contact|Easy|AC|1|N/A
Why Did the Cow Cross the Road II|Normal|AC|1|N/A
Swap|Normal|AC|3|Understand that at most `|S| * (|S| - 1) / 2` swaps are needed to produce any permutation of string `S`. We can use paths on grids keeping track of the number of visited 'K', 'E' and 'Y' as well as the number of swaps used to find all unique strings possible with at most `min(K, |S| * (|S| - 1) / 2)` swaps.
Palindromic Paths|Hard|AC|2|Understand that we can assign each upward sloping diagonal to a corresponding row and each downward sloping diagonal to a column. This way, each index in a palindrome corresponds to a "row" and the last visited character to a "column". Paths ending up at the same row and column after `n` upward diagonals are palindromes.
Pair Programming|Hard|AC|1|Understand that there are only a few "critical" characters: '+', '0', '1' and ['2', '9']. If a character is a '+', its uniqueness is determined by its position. This is because all characters before the '+' (and after the last '+') must have been contributed already and from the position, the number of characters from the other string can be found. Since, the same set of characters are used among all combinations, their product must always be the same (unless among the characters exists a '0'). Meanwhile, if a set of instructions ends with '0', its program must be equal to '0'. Dynamic programming can be used to prevent double-counting this case. If the instructions contain any number of '1's, its resulting program would be the same even without the '1's, so the '1's can be filtered out. Lastly, all other numbers affect the program, but their order does not matter,as stated when explaining '+'.