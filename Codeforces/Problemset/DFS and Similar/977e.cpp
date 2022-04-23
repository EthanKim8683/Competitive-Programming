#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using B = bool;

vector<I> adjs[200000];
B visited[200000];

B dfs(I v, I p) {
  visited[v] = true;
  const auto adj = adjs[v];
  B result = adj.size() == 2;
  for (const auto u : adjs[v])
    if (u != p && !visited[u])
      result &= dfs(u, v);
  return result;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("977e.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  while (m--) {
    I v, u;
    cin >> v >> u;
    v--;
    u--;
    adjs[v].push_back(u);
    adjs[u].push_back(v);
  }
  I result = 0;
  for (I i = n; i--;)
    if (!visited[i])
      result += dfs(i, -1);
  printf("%i\n", result);
  return 0;
}