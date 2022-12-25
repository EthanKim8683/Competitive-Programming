#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 100;
const I MAX = 1e9;

I a_arr[N];
I dp[N + 1][N + 1][N + 1];

void cmb(I& a, I b) {
  a = min(a, b);
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("taming.in", "r", stdin);
  freopen("taming.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(I), MAX);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  dp[1][1][1] = a_arr[0] != 0;
  for (I i = 1; i < n; i++) {
    const I a = a_arr[i];
    for (I j = 0; j <= i; j++) {
      for (I k = 0; k <= i; k++) {
        cmb(dp[i + 1][j + 1][k], dp[i][j][k] + (a != j));
        cmb(dp[i + 1][1][k + 1], dp[i][j][k] + (a != 0));
      }
    }
  }
  for (I i = 1; i <= n; i++) {
    I res = MAX;
    for (I j = 0; j <= n; j++)
      cmb(res, dp[n][j][i]);
    printf("%i\n", res);
  }
  return 0;
}