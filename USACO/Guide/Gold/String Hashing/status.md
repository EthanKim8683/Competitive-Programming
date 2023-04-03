# Practice Problems Status
Problem|Rating|Correct cases|Attempts|Notes
-|-|-|-|-
Searching For Strings|Easy|AC|2|Using a frequency list to find matches and hashing to store permutations suffices.
Finding Periods|Very Easy|AC|1|Understand that checking all possible period lengths takes `O(N * ln(N))` with the aid of string hashing's `O(1)` comparisons.
Censoring|Easy|AC|1|Using stack, queue and two pointers, we can test  at every index `i` in `s`, a `t`-sized block ending at `i`. If it matches with `t`, we remove it.
2017 - Palindromic Partitions|Easy|AC|1|Understand that partitions can be greedily created.
Palindromic Characteristics|Easy|AC|9|Understand that the `k` of a `k`-palindrome can be at most `log2(N)`. This is because each `k`-palindrome requires two non-empty `(k - 1)`-palindromes, which themselves require two non-empty `(k - 2)`-palindromes, and so on. Using this, we can use dynamic programming to determine the total number of `k`-palindromes for each `k` in `O(log2(N) * N ^ 2)`.
Check Transcription|Easy|DNF|0|N/A
Bovine Genomics|Normal|DNF|0|N/A
Lights Out|Normal|DNF|0|N/A
2017 - Hangman 2|Normal|DNF|0|N/A
2017 - Osmosmjerka|Normal|DNF|0|N/A
2012 - Sateliti|Hard|DNF|0|N/A
Liar|Hard|DNF|0|N/A
2018 - Genetics|Hard|DNF|0|N/A
2016 - Zamjene|Very Hard|DNF|0|N/A
2016 - Palinilap|Very Hard|DNF|0|N/A