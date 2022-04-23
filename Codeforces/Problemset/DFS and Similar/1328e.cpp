#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using U = unsigned;
using B = bool;

vector<U> adjs[200000];
U parents[200000];
U depths[200000];
U tour_beg[200000];
U tour_end[200000];
U v_parents[200000];
U timer = 0;

void dfs(U a, U parent, U depth) {
  parents[a] = parent;
  depths[a] = depth;
  depth++;
  tour_beg[a] = timer;
  timer++;
  for (const auto b : adjs[a])
    if (b != parent)
      dfs(b, a, depth);
  tour_end[a] = timer;
  timer++;
}

B is_ancestor(U a, U b) {
  return tour_beg[a] < tour_beg[b] &&
         tour_end[a] > tour_end[b];
}

int main(void) {
#if defined(ETHANKIM8683)
  freopen("1382e.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, m;
  cin >> n >> m;
  for (U i = n; --i;) {
    U u, v;
    cin >> u >> v;
    u--;
    v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  dfs(0, -1, 0);
  while (m--) {
    U k;
    cin >> k;
    U end_index = 0;
    U end_depth = 0;
    for (U i = k; i--;) {
      U v;
      cin >> v;
      v--;
      const U v_depth = depths[v];
      if (v_depth > end_depth) {
        end_depth = v_depth;
        end_index = v;
      }
      v_parents[i] = parents[v];
    }
    B result = true;
    for (U i = k; result && i--;) {
      const U parent = v_parents[i];
      if (parent != -1)
        result = is_ancestor(parent, end_index);
    }
    if (result)
      printf("YES\n");
    else
      printf("NO\n");
  }
  return 0;
}