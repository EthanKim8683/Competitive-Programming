# Practice Problem Notes

## [1382E](https://codeforces.com/problemset/problem/1328/E) - Tree Queries

### Problem:

Include nodes of distance 1 to the path.

<h3 id="tree-erosion">Solution: Tree Erosion</h3>

```cpp
#include <vector>

using namespace std;

const int N = 100000;

vector<int> adjs[N];
int parents[N];
int eroded[N];

// Store parents of all nodes to be eroded later.
void dfs(int a, int parent) {
  parents[a] = parent;
  for (const auto b : adjs[a])
    if (b != parent)
      dfs(b, a);
}

// Store eroded nodes in an `eroded` array.
void erode(int length, int* nodes) {
  for (int i = 0; i < length; i++)
    eroded[i] = parents[nodes[i]];
}
```

Replace nodes with their parents to simulate erosion of tree.

<br>

### Problem:

Determine if there is a branchless path connecting all nodes.

<h3 id="euler-tour">Solution: Euler Tour</h3>

```cpp
#include <vector>

using namespace std;

const int N = 100000;

vector<int> adjs[N];
int tour_begs[N];
int tour_ends[N];
int timer;

// Initialize ranges: all decendants of a node will be
// within said node's range.
void dfs(int a, int parent) {
  tour_begs[a] = timer;
  timer++;
  for (const auto b : adjs[a])
    if (b != parent)
      dfs(b, a);
  tour_ends[b] = timer;
  timer++;
}

// Given the aforementioned property, it's possible to
// check if node `a` is an ancestor of node `b` by checking
// if node `b`'s range is inside of node `a`'s range.
bool is_anc(int a, int b) {
  return tour_begs[a] < tour_begs[b] &&
         tour_ends[a] > tour_ends[b];
}
```

Check if all nodes are ancestors of the end node.

<br>

## [1242B](https://codeforces.com/problemset/problem/1242/B) - 0-1 MST

### Problem:

Find minimum spanning tree of a graph where all edges are of weight 1 or 0.

<h3 id="inverted-search">Solution: Inverted Search</h3>

```cpp
#include <set>
#include <unordered_set>

using namespace std;

const int N = 100000;

unordered_set<int> adjs[N];
set<int> unvisited;

// Store unvisited nodes in a set such that `upper_bound`
// could be used to find the next unvisited node in
// O(log(n)) complexity (where n is also decreasing).
// Store inverted edges in an unsorted set to ensure
// constant time when checking.
void dfs(int a) {
  auto& adj = adjs[a];
  auto it = unvisited.begin();
  while (it != unvisited.end()) {
    const auto b = *it;
    if (adj.find(b) == adj.end()) {
      unvisited.erase(it);
      dfs(b);
      it = unvisited.upper_bound(b);
    } else
      it++;
  }
}

// Initialize unvisited nodes
void init(int n) {
  for (int i = 0; i < n; i++)
    unvisited.insert(i);
}
```

Count the total subgraphs connected by only 0-weight edges and subtract 1 to get the number of edges to connect them.

<br>

## [191C](https://codeforces.com/problemset/problem/191/C) - Fools and Roads

### Problem:

Find the least common ancestor of two nodes, marking the highest point of the path between them.

<h3 id="binary-lifting">Solution: LCA with <a href="#euler-tour">Euler Tour</a> and Binary Lifting</h3>

```cpp
#include <vector>

using namespace std;

const int N = 100000;
const int LOGN = 17;

vector<int> adjs[N];
int ancs[N][LOGN];
int tour_begs[N];
int tour_ends[N];
int timer = 0;

// Initialize binary lifting: each node stores the 1st
// ancestor above it, the 2nd, 4th, 8th, 16th, 32nd, etc.
// Make sure the root's parent is itself, and not -1.
void dfs(int a, int parent) {
  tour_begs[a] = timer;
  timer++;
  ancs[a][0] = parent;
  for (int i = 1; i < LOGN; i++)
    ancs[a][i] = ancs[ancs[a][i - 1]][i - 1];
  for (const auto b : adjs[a])
    if (b != parent)
      dfs(b, a);
  tour_ends[a] = timer;
  timer++;
}

// Note that this implementation of `is_anc` is inclusive
// of the `a == b` case. This is to prevent `a` from
// converging onto `b` in binary lifting in the case that
// `b` is the LCA.
bool is_anc(int a, int b) {
  return tour_begs[a] <= tour_begs[b] &&
         tour_ends[a] >= tour_ends[b];
}

// In this LCA function, binary lifting is used to
// converge onto the child of the lowest common ancestor
// of `a` and `b` in O(log(n)) complexity.
int lca(int a, int b) {
  if (is_anc(a, b))
    return a;
  if (is_anc(b, a))
    return b;
  for (int i = LOGN - 1; i >= 0; i--)
    if (!is_anc(ancs[a][i], b))
      a = ancs[a][i];
  return ancs[a][0];
}
```

<br>

### Problem:

Find how many times an edge is visited.

<h3 id="prefix-sums">Solution: Prefix Sums</h3>

```cpp
#include <vector>

using namespace std;

const int N = 100000;

vector<pair<int, int>> adjs[N];
int ps[N];
int visits[N];

// By subtracting 1 from the higher node's prefix and
// adding 1 to the lower node's prefix for each direct
// path starting and ending at those nodes, we can add the
// prefix of each node as we traverse up the tree and the
// resulting value each time is the number of visits to
// that node.
int dfs(int a, int parent) {
  int sum = ps[a];
  for (const auto [b, edge] : adjs[a]) {
    if (b != parent) {
      visits[edge] = dfs(b, a);
      sum += visits[edge];
    }
  }
  return sum;
}
```

<br>

## [1272E](https://codeforces.com/problemset/problem/1272/E) - Nearest Opposite Parity

### Problem:

Find the nearest opposite parity.

<h3 id="bfs">Solution: BFS</h3>

```cpp
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int N = 100000;

vector<int> adjs[N];
queue<int> states;
int dists[N];
int n;

// Starting with node(s) of 0 distance to itself, nodes
// set adjacent nodes to 1 more than their own distance,
// as they are 1 away. Each node need only be visited once
// because the distances are monotonically increasing with
// respect to the number of iterations, and the algorithm
// aims to find a minimum distance.
void bfs() {
  while (!states.empty()) {
    const auto a = states.front();
    states.pop();
    const auto dist = dists[a] + 1;
    for (const auto b : adjs[a]) {
      if (dists[b] == 1e9) {
        dists[b] = dist;
        states.push(b);
      }
    }
  }
}

// Initialize unvisited nodes/maximum distances
void init() {
  fill(dists, dists + n, 1e9);
}
```
This approach may be used with multiple nodes at once to find the minimum distance to any node, as with the solution to this problem.

<br>

## [343D](https://codeforces.com/contest/343/problem/D) - Water Tree

### Problem:

<h3 id="segment-tree">Solution: <a href="#euler-tour">Euler Tour</a> and Segment Tree</h3>

```cpp
#include <vector>

using namespace std;

const int N = 500000;
const int SEG = 1048576;

vector<int> adjs[N];
int range_segs[SEG];
int point_segs[SEG];
int tour_begs[N];
int tour_ends[N];
int timer = 0;
int n;

// Initialize Euler tour ranges.
void dfs(int a, int parent = -1) {
  tour_begs[a] = timer;
  timer++;
  for (const auto b : adjs[a])
    if (b != parent)
      dfs(b, a);
  tour_ends[a] = timer;
}

// Set a single value in a segment tree. Traverses up the
// binary segment tree (bintree) in O(log(N)) time, updating
// every ancestor segment. This segment tree is used to
// find the maximum value of a range and thus, has a
// `max(a, b)` transition. It's also possible to find range
// sums using `a + b` instead.
void range_update(int i, int value) {
  i += n;
  range_segs[i] = value;
  while (i > 1) {
    range_segs[i >> 1] = max(range_segs[i], range_segs[i ^ 1]);
    i >>= 1;
  }
}

// Get a range-accumulated value from a segment tree.
// Accumulate power-of-two chunks of segments in O(log(N))
// time. This works because the segment tree contains
// log2(N) layers of increasing detail with respect to
// depth.
int range_query(int l, int r) {
  int result = 0;
  l += n;
  r += n;
  while (l < r) {
    if (l & 1) {
      result = max(result, range_segs[l]);
      l++;
    }
    if (r & 1) {
      r--;
      result = max(result, range_segs[r]);
    }
    l >>= 1;
    r >>= 1;
  }
  return result;
}

// Set a range of values in a segment tree. Unlike the
// previous pair of functions, this implementation handles
// an update range and a query point, versus an update point
// and a query range. Traversal is similar to the previous
// `range_query` function.
void point_update(int l, int r, int value) {
  l += n;
  r += n;
  while (l < r) {
    if (l & 1) {
      point_segs[l] = value;
      l++;
    }
    if (r & 1) {
      r--;
      point_segs[r] = value;
    }
    l >>= 1;
    r >>= 1;
  }
}

// Traversal is similar to the `range_update` function,
// meanwhile processing is similar to the `range_query`
// function.
int point_query(int i) {
  int result = 0;
  i += n;
  while (i > 0) {
    result = max(result, point_segs[i]);
    i >>= 1;
  }
  return result;
}
```

<br>