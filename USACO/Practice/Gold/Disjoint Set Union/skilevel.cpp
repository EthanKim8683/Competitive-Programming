#include <iostream>
#include <cstdio>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;
using Lli = long long int;

const I M = 500;
const I N = 500;
const I MAX = 1e9;

I eles[M][N];
B stas[M][N];
I pars[M * N];
I ress[M * N];
B viss[M * N];
vector<I> adjs[M * N];
vector<tuple<I, I, I>> edgs;
I m, n;

I cps(I i, I j) {
  return i * n + j;
}

I fnd(I x) {
  if (pars[x] < 0)
    return x;
  return pars[x] = fnd(pars[x]);
}

B uni(I a, I b) {
  if ((a = fnd(a)) == (b = fnd(b)))
    return false;
  if (pars[a] > pars[b])
    swap(a, b);
  pars[a] += pars[b];
  pars[b] = a;
  return true;
}

B con(I a, I b) {
  return fnd(a) == fnd(b);
}

I siz(I x) {
  return -pars[fnd(x)];
}

void fil(I a, I d) {
  if (viss[a])
    return;
  viss[a] = true;
  ress[a] = d;
  for (const auto b : adjs[a])
    if (con(a, b))
      fil(b, d);
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("skilevel.in", "r", stdin);
  freopen("skilevel.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> m >> n >> t;
  for (I i = 0; i < m; i++)
    for (I j = 0; j < n; j++)
      cin >> eles[i][j];
  for (I i = 0; i < m; i++)
    for (I j = 0; j < n; j++)
      cin >> stas[i][j];
  fill_n(pars, m * n, -1);
  for (I i = 0; i < m; i++) {
    for (I j = 0; j < n; j++) {
      if (i + 1 < m) {
        const I a = cps(i, j);
        const I b = cps(i + 1, j);
        adjs[a].push_back(b);
        adjs[b].push_back(a);
        edgs.push_back({abs(eles[i][j] - eles[i + 1][j]), a, b});
      }
      if (j + 1 < n) {
        const I a = cps(i, j);
        const I b = cps(i, j + 1);
        adjs[a].push_back(b);
        adjs[b].push_back(a);
        edgs.push_back({abs(eles[i][j] - eles[i][j + 1]), a, b});
      }
    }
  }
  sort(edgs.begin(), edgs.end());
  for (const auto [d, a, b] : edgs) {
    const I a_par = fnd(a);
    const I b_par = fnd(b);
    if (uni(a, b) && siz(a) >= t) {
      fil(a_par, d);
      fil(b_par, d);
    }
  }
  Lli res = 0;
  for (I i = 0; i < m; i++)
    for (I j = 0; j < n; j++)
      if (stas[i][j])
        res += ress[cps(i, j)];
  printf("%lli\n", res);
  return 0;
}