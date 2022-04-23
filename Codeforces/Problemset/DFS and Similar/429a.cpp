#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using B = bool;

vector<I> adjs[100000];
B init[100000];
B goal[100000];
I ops[100000];
I cnt = 0;

void dfs1(I u, I p = -1, I a = 0, I b = 0) {
  if (a ^ init[u] != goal[u]) {
    ops[cnt] = u + 1;
    cnt++;
    a ^= 1;
  }
  for (const auto v : adjs[u])
    if (v != p)
      dfs1(v, u, b, a);
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("429a.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = n; --i;) {
    I u, v;
    cin >> u >> v;
    u--;
    v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  for (I i = 0; i < n; i++)
    cin >> init[i];
  for (I i = 0; i < n; i++)
    cin >> goal[i];
  dfs1(0);
  printf("%i\n", cnt);
  for (I i = 0; i < cnt; i++)
    printf("%i\n", ops[i]);
  return 0;
}