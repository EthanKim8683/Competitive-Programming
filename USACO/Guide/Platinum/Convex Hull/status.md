# Practice Problems Status
Problem|Rating|Correct cases|Attempts|Notes
-|-|-|-|-
Convex Hull|Easy|AC|1|For Graham Scan: Set the bottom left-most point as the root of the hull and sort the remaining points by angle. Then wrap the hull around using a stack, popping while the current node makes a "right turn", making the hull concave. For Monotone Chain: Sort by `x` coordinate, and then create an upper (decreasing `x`) and a lower hull (increasing `x`) such that every point in either hull contributes positive area locally in the direction of the hull.
Robert Hood|Easy|AC|3|Using Shamos's algorithm (without angles), we can find the antipodal pairs and then maximize for distance. The basic idea of this algorithm is that, for each node `i`, there is a node `j` such that the distance between `i` and `j` is maximal among all nodes. Using two pointers (as for all `i1 > i0`, `j1 > j0`), we can find `j` for each `i` until a solved `i` or `j` has been reached, resulting in a set of all antipodal pairs.
Water Balance|Easy|AC|1|Understand that the resulting prefix sum array of the answer should be monotonically increasing in slope, otherwise a better answer exists. Finding the convex hull of the original prefix sum array guarantees this is the case (otherwise the hull would not be convex).
Balance Beam|Normal|AC|1|Although I solved this problem on my own (and first try too), somehow I had a completely wrong reasoning. TODO: solve this problem properly.
Geometers Anonymous|Normal|AC|1|Note that the number of points in a Minkowski sum is equal to the total number of unique edges from each of its constituents.
Cow Curling|Normal|AC|1|Understand that two pointers may be used to keep track of the relevant bounds for each opponent stone.
Fence Orthogonality|Hard|AC|1|Understand that the finding function of Shamos's algorithm can be applied in a perpendicular fashion to find the remaining sides of the bounding box for a given pair of antipodal points.
2011 - Timeismoney|Hard|DNF|0|N/A
AGC E - Random Pawn|Very Hard|DNF|0|N/A