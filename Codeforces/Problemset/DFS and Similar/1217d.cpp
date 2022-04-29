#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 5000;
const I M = 5000;

vector<pair<I, I>> adjs[N];
vector<I> edgs[M];
pair<I, I> pars[N];
I viss[N];
I cycs[N];
I cols[M];
I inds[M];
I ress[M];
I ind = 0;

// cycle detection is incorrect
void dfs(I a) {
  viss[a] = 1;
  for (const auto [b, i] : adjs[a]) {
    if (viss[b] == 0) {
      pars[b] = {a, i};
      dfs(b);
    } else if (viss[b] == 1) {
      I l = a;
      edgs[i].emplace_back(ind);
      while (l != b) {
        const auto [n, i] = pars[l];
        edgs[i].emplace_back(ind);
        l = n;
      }
      ind++;
    }
  }
  viss[a] = 2;
}

B cmp(I a, I b) {
  return edgs[a].size() < edgs[b].size();
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("1217d.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  for (I i = 0; i < m; i++) {
    I u, v;
    cin >> u >> v;
    adjs[u - 1].emplace_back(v - 1, i);
  }
  for (I i = n; i--;)
    if (!viss[i])
      dfs(i);
  for (I i = m; i--;)
    inds[i] = i;
  sort(inds, inds + m, cmp);
  I k = 0;
  for (I i = 0; i < m; i++) {
    for (const auto cyc : edgs[inds[i]])
      if (cycs[cyc] > 0)
        cols[cycs[cyc]] = true;
    I col = 1;
    while (cols[col]) {
      cols[col] = false;
      col++;
    }
    k = max(k, col);
    for (const auto cyc : edgs[inds[i]]) {
      if (cycs[cyc] > 0)
        cycs[cyc] = -1;
      else if (cycs[cyc] == 0)
        cycs[cyc] = col;
    }
    ress[inds[i]] = col;
  }
  printf("%i\n", k);
  for (I i = 0; i < m; i++)
    printf("%i ", ress[i]);
  return 0;
}