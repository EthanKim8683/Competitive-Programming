#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

using U = unsigned;
using Llu = long long unsigned;
using B = bool;

vector<U> adjs[100000];
B visited[100000];
U a_dists[100000];
U b_dists[100000];
U roots[100000];

void dfs(U a, U root) {
  if (visited[a])
    return;
  visited[a] = true;
  roots[a] = root;
  for (const auto b : adjs[a])
    dfs(b, root);
}

int main(void) {
#if defined(ETHANKIM8683)
  freopen("barns.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U t;
  cin >> t;
  while (t--) {
    U n, m;
    cin >> n >> m;
    for (U i = n; i--;)
      adjs[i].clear();
    memset(visited, false, n * sizeof(B));
    memset(a_dists, -n, n * sizeof(U));
    memset(b_dists, -n, n * sizeof(U));
    while (m--) {
      U i, j;
      cin >> i >> j;
      i--;
      j--;
      adjs[i].push_back(j);
      adjs[j].push_back(i);
    }
    for (U i = n; i--;)
      dfs(i, i);
    const U a_root = roots[0];
    const U b_root = roots[n - 1];
    U a_dist = 0;
    U b_dist = -n;
    for (U i = 0; i < n; i++) {
      const U root = roots[i];
      if (root == a_root)
        a_dist = 0;
      if (root == b_root)
        b_dist = 0;
      a_dists[root] = min(a_dists[root], a_dist);
      b_dists[root] = min(b_dists[root], b_dist);
      a_dist++;
      b_dist++;
    }
    a_dist = -n;
    b_dist = 0;
    for (U i = n; i--;) {
      const U root = roots[i];
      if (root == a_root)
        a_dist = 0;
      if (root == b_root)
        b_dist = 0;
      a_dists[root] = min(a_dists[root], a_dist);
      b_dists[root] = min(b_dists[root], b_dist);
      a_dist++;
      b_dist++;
    }
    Llu result = -1;
    for (U i = n; i--;) {
      const U root = roots[i];
      const Llu a_dist = a_dists[root];
      const Llu b_dist = b_dists[root];
      result = min(result, a_dist * a_dist + b_dist * b_dist);
    }
    printf("%llu\n", result);
  }
  return 0;
}