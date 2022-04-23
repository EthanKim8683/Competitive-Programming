#include <iostream>
#include <cstdio>
#include <vector>

#define LOGN 20

using namespace std;

using I = int;
using B = bool;

vector<pair<I, I>> adjs[200000];
I anc[200000][LOGN];
I tour_beg[200000];
I tour_end[200000];
I result[200000];
I ps[200000];
I timer = 0;

void dfs1(I u, I p) {
  tour_beg[u] = timer++;
  anc[u][0] = p;
  for (I i = 1; i < LOGN; i++)
    anc[u][i] = anc[anc[u][i - 1]][i - 1];
  for (const auto [v, i] : adjs[u])
    if (v != p)
      dfs1(v, u);
  tour_end[u] = timer++;
}

B is_anc(I u, I v) {
  return tour_beg[u] <= tour_beg[v] &&
         tour_end[u] >= tour_end[v];
}

I lca(I u, I v) {
  if (is_anc(u, v))
    return u;
  if (is_anc(v, u))
    return v;
  for (I i = LOGN; i--;)
    if (!is_anc(anc[u][i], v))
      u = anc[u][i];
  return anc[u][0];
}

I dfs2(I u, I p) {
  I sum = ps[u];
  for (const auto [v, i] : adjs[u]) {
    if (v != p) {
      result[i] = dfs2(v, u);
      sum += result[i];
    }
  }
  return sum;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("191c.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n - 1; i++) {
    I u, v;
    cin >> u >> v;
    u--;
    v--;
    adjs[u].push_back({v, i});
    adjs[v].push_back({u, i});
  }
  dfs1(0, 0);
  I k;
  cin >> k;
  while (k--) {
    I a, b;
    cin >> a >> b;
    a--;
    b--;
    ps[a]++;
    ps[b]++;
    ps[lca(a, b)] -= 2;
  }
  dfs2(0, -1);
  for (I i = 0; i < n - 1; i++)
    printf("%u ", result[i]);
}