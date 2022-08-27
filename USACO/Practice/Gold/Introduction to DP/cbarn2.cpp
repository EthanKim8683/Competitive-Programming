#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 100;
const I K = 7;
const Lli MAX = 1e18;

I r_arr[N];
Lli ps[N + 1];
Lli dp[N][N][K + 1];
I n;

Lli rng(I l, I r) {
  return ps[r] - ps[l];
}

Lli cut(I l, I m, I r) {
  return (rng(0, l) + rng(r, n)) * (r - m);
}

void cmb(Lli& a, Lli b) {
  a = min(a, b);
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("cbarn2.in", "r", stdin);
  freopen("cbarn2.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(Lli), MAX);
  I k;
  cin >> n >> k;
  for (I i = 0; i < n; i++)
    cin >> r_arr[i];
  if (k >= n) {
    printf("0\n");
    return 0;
  }
  for (I i = 0; i < n; i++)
    ps[i + 1] = ps[i] + r_arr[i];
  Lli cur = 0;
  Lli tot = 0;
  for (I i = n - 1; i >= 0; i--) {
    cur += tot;
    tot += r_arr[i];
  }
  for (I i = 0; i < n; i++) {
    for (I j = 0; j < i; j++)
      for (I l = j; l < i; l++)
        for (I m = k - 1; m >= 1; m--)
          cmb(dp[j][i][m + 1], dp[j][l][m] - cut(j, l, i));
    dp[i][i][1] = cur;
    cur += n * r_arr[i] - tot;
  }
  Lli res = MAX;
  for (I i = 0; i < n; i++)
    for (I j = 0; j < n; j++)
      cmb(res, dp[i][j][k]);
  printf("%lli\n", res);
  return 0;
}