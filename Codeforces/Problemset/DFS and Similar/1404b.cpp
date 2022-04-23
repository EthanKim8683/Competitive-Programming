#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using U = unsigned;
using B = bool;

vector<U> adjs[100000];
U depth = 0;
U diameter = 0;
U b;
U b_depth;

U dfs(U a, U p) {
  if (a == b)
    b_depth = depth;
  depth++;
  U a_max = 0;
  U b_max = 0;
  for (const auto b : adjs[a]) {
    if (b != p) {
      const U c_max = dfs(b, a);
      if (c_max >= a_max) {
        b_max = a_max;
        a_max = c_max;
      } else if (c_max > b_max)
        b_max = c_max;
    }
  }
  depth--;
  diameter = max(diameter, a_max + b_max);
  return a_max + 1;
}

int main(void) {
#if defined(ETHANKIM8683)
  freopen("1404b.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U t;
  cin >> t;
  while (t--) {
    U n, a, da, db;
    cin >> n >> a >> b >> da >> db;
    a--;
    b--;
    const U range = da * 2;
    if (range >= db) {
      while (--n) {
        U u, v;
        cin >> u >> v;
      }
      printf("Alice\n");
    } else {
      for (U i = n; i--;)
        adjs[i].clear();
      while (--n) {
        U u, v;
        cin >> u >> v;
        u--;
        v--;
        adjs[u].push_back(v);
        adjs[v].push_back(u);
      }
      diameter = 0;
      dfs(a, -1);
      if (da >= b_depth || range >= diameter)
        printf("Alice\n");
      else
        printf("Bob\n");
    }
  }
  return 0;
}