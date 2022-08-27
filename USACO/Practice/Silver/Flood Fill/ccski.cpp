#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I M = 500;
const I N = 500;
const I D = 1000000000;

I higs[M][N];
B ways[M][N];
B viss[M][N];
vector<pair<I, I>> pnts;
I m, n;

B bnd(I i, I j) {
  return i >= 0 && i < m && j >= 0 && j < n;
}

void dfs(I i, I j, I p, I d) {
  const I hig = higs[i][j];
  if (!bnd(i, j) || abs(hig - p) > d || viss[i][j])
    return;
  viss[i][j] = true;
  dfs(i - 1, j, hig, d);
  dfs(i + 1, j, hig, d);
  dfs(i, j - 1, hig, d);
  dfs(i, j + 1, hig, d);
}

B tes(I d) {
  fill(&viss[0][0], &viss[0][0] + sizeof(viss) / sizeof(B), false);
  const auto [i, j] = pnts[0];
  dfs(i, j, higs[i][j], d);
  for (const auto [i, j] : pnts)
    if (!viss[i][j])
      return false;
  return true;
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("ccski.in", "r", stdin);
  freopen("ccski.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> m >> n;
  for (I i = 0; i < m; i++)
    for (I j = 0; j < n; j++)
      cin >> higs[i][j];
  for (I i = 0; i < m; i++)
    for (I j = 0; j < n; j++)
      cin >> ways[i][j];
  for (I i = 0; i < m; i++)
    for (I j = 0; j < n; j++)
      if (ways[i][j])
        pnts.push_back({i, j});
  if (pnts.empty()) {
    printf("0\n");
    return 0;
  }
  I l = 0;
  I r = D;
  while (l < r) {
    const I m = l + (r - l) / 2;
    if (tes(m))
      r = m;
    else
      l = m + 1;
  }
  printf("%i\n", l);
  return 0;
}