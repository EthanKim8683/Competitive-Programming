#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;
using Lli = long long int;

vector<I> adjs[200000];
B a_visited[200000];
B b_visited[200000];

void dfs(I u, I x, B* visited) {
  if (u == x || visited[u])
    return;
  visited[u] = true;
  for (const auto v : adjs[u])
    dfs(v, x, visited);
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("1276b.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I n, m, a, b;
    cin >> n >> m >> a >> b;
    fill_n(a_visited, n, false);
    fill_n(b_visited, n, false);
    a--;
    b--;
    for (I i = n; i--;)
      adjs[i].clear();
    while (m--) {
      I u, v;
      cin >> u >> v;
      u--;
      v--;
      adjs[u].push_back(v);
      adjs[v].push_back(u);
    }
    dfs(a, b, a_visited);
    dfs(b, a, b_visited);
    Lli a_count = -1;
    Lli b_count = -1;
    for (I i = n; i--;) {
      const B a_visit = a_visited[i];
      const B b_visit = b_visited[i];
      if (a_visit != b_visit) {
        if (a_visit)
          a_count++;
        else
          b_count++;
      }
    }
    printf("%lli\n", a_count * b_count);
  }
  return 0;
}