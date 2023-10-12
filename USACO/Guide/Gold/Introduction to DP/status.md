# Practice Problems Status
Problem|Rating|Correct cases|Attempts|Notes
-|-|-|-|-
Frog 1|Easy|AC|2|N/A
Mortal Kombat Tower|Easy|AC|2|N/A
Hoof Paper Scissors|Easy|AC|1|N/A
Time is Mooney|Easy|AC|1|N/A
Teamwork|Normal|AC|1|N/A
Snakes|Normal|AC|2|N/A
Phidias|Normal|AC|1|N/A
Moving to the Capital|Hard|AC|2|N/A
Circular Barn Revisited|Hard|AC|1|N/A
Taming the Herd|Hard|AC|1|N/A
Drought|Hard|AC|1|N/A
Moortal Cowmbat|Hard|AC|1|N/A
Team Building|Hard|AC|1|N/A
Stamp Painting|Very Hard|AC|1|N/A
Bovine Genetics|Very Hard|AC|1|Understand that keeping track of the number of previous segments $[l, r]$ based on $\textit{genome}[l]$, $\textit{genome}[r + 1]$ (the beginning of the segment immediately after; becomes $\textit{genome}[l]$ post-transition) allows us to, at index $i$, easily transition for all $\textit{genome}[i] = \textit{genome}[l]$, representing two adjacent segments split along two consecutive equal characters in the unedited genome. However, if two adjacent characters are equal in the edited genome, they must belong to different segments. This is because all pairs of adjacent equal characters are divided into different segments during the editing process. To handle this, we also keep track of $\textit{prev}$, the previous character, and, if $\textit{genome[i]} = prev$, transitions can no longer occur from prefixes before this point.