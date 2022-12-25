#include <iostream>
#include <cstdio>
#include <algorithm>
#include <tuple>

using namespace std;

using I = int;
using B = bool;

const I N = 1000;
const I MAX = 1e9;
const I MIN = -1e9;

I cols[N][N];
B viss1[N][N];
B viss2[N][N];
I ps[N + 1][N + 1];
B poss[N * N + 1];
I mins1[N * N + 1];
I mins2[N * N + 1];
I maxs1[N * N + 1];
I maxs2[N * N + 1];
I n;

B bnd(I i, I j) {
  return i >= 0 && i < n && j >= 0 && j < n;
}

void cmb1(I& a, I b) {
  a = min(a, b);
}

void cmb2(I& a, I b) {
  a = max(a, b);
}

void fil1(I i, I j, I col) {
  if (!bnd(i, j) || viss1[i][j] || cols[i][j] != col)
    return;
  viss1[i][j] = true;
  cmb1(mins1[col], i);
  cmb1(mins2[col], j);
  cmb2(maxs1[col], i);
  cmb2(maxs2[col], j);
  fil1(i - 1, j, col);
  fil1(i + 1, j, col);
  fil1(i, j - 1, col);
  fil1(i, j + 1, col);
}

void fil2(I i, I j, I col) {
  if (!bnd(i, j) || viss2[i][j] || cols[i][j] != col)
    return;
  viss2[i][j] = true;
  poss[col] &= ps[i][j] <= 1;
  fil2(i - 1, j, col);
  fil2(i + 1, j, col);
  fil2(i, j - 1, col);
  fil2(i, j + 1, col);
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("art.in", "r", stdin);
  freopen("art.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = 0; i < n; i++)
    for (I j = 0; j < n; j++)
      cin >> cols[i][j];
  fill_n(mins1 + 1, n * n, MAX);
  fill_n(mins2 + 1, n * n, MAX);
  fill_n(maxs1 + 1, n * n, MIN);
  fill_n(maxs2 + 1, n * n, MIN);
  fill_n(poss + 1, n * n, true);
  for (I i = 0; i < n; i++)
    for (I j = 0; j < n; j++)
      fil1(i, j, cols[i][j]);
  I cnt = 0;
  for (I i = 1; i <= n * n; i++) {
    const I min1 = mins1[i];
    const I min2 = mins2[i];
    const I max1 = maxs1[i];
    const I max2 = maxs2[i];
    if (min1 > max1 || min2 > max2)
      continue;
    ps[min1][min2]++;
    ps[min1][max2 + 1]--;
    ps[max1 + 1][min2]--;
    ps[max1 + 1][max2 + 1]++;
    cnt++;
  }
  for (I i = 0; i < n; i++) {
    for (I j = 0; j < n; j++) {
      if (i - 1 >= 0)
        ps[i][j] += ps[i - 1][j];
      if (j - 1 >= 0)
        ps[i][j] += ps[i][j - 1];
      if (i - 1 >= 0 && j - 1 >= 0)
        ps[i][j] -= ps[i - 1][j - 1];
    }
  }
  for (I i = 0; i < n; i++)
    for (I j = 0; j < n; j++)
      fil2(i, j, cols[i][j]);
  I res = 0;
  for (I i = 1; i <= n * n; i++)
    res += poss[i];
  printf("%i\n", res - (cnt <= 1));
  return 0;
}