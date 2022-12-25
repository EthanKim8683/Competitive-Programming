#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using S = string;
using B = bool;
using Lli = long long int;

const I N = 100000;
const Lli MAX = 1e18;

S nams[N];
B fils[N];
vector<I> chis[N];
vector<pair<I, I>> adjs[N];
I dp1[N];
Lli dp2[N][2];

void dfs1(I a) {
  dp1[a] = adjs[a].empty();
  for (const auto [b, len] : adjs[a]) {
    dfs1(b);
    dp1[a] += dp1[b];
    dp2[a][0] += dp1[b] * len + dp2[b][0];
  }
}

void dfs2(I a) {
  for (const auto [b, len] : adjs[a]) {
    dp2[b][1] += dp2[a][0] - (dp1[b] * len + dp2[b][0]);
    dp2[b][1] += dp2[a][1];
    dp2[b][1] += (dp1[0] - dp1[b]) * 3;
    dfs2(b);
  }
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("dirtraverse.in", "r", stdin);
  freopen("dirtraverse.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    S nam;
    I m;
    cin >> nam >> m;
    if (m != 0)
      nam += "/";
    nams[i] = nam;
    for (I j = 0; j < m; j++) {
      I id;
      cin >> id;
      chis[i].push_back(id - 1);
    }
  }
  for (I i = 0; i < n; i++)
    for (const auto id : chis[i])
      adjs[i].push_back({id, nams[id].size()});
  dfs1(0);
  dfs2(0);
  Lli res = MAX;
  for (I i = 0; i < n; i++)
    if (!adjs[i].empty())
      res = min(res, dp2[i][0] + dp2[i][1]);
  printf("%lli\n", res);
  return 0;
}