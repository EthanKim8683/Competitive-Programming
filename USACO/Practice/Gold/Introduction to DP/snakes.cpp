#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I MAX = 1e9;
const I N = 400;
const I K = N - 1;

pair<I, I> dp[2][K + 1][N + 1];

I main(void) {
  freopen("snakes.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("snakes.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, k;
  cin >> n >> k;
  for (I i = 0; i <= k; i++) {
    fill_n(dp[0][i], n + 1, pair<I, I>{MAX, 0});
    fill_n(dp[1][i], n + 1, pair<I, I>{MAX, 0});
  }
  dp[0][0][0] = {0, 0};
  for (I i = 0; i < n; i++) {
    I a;
    cin >> a;
    for (I j = 0; j <= k; j++) {
      for (I l = 0; l <= n; l++) {
        auto [tot, siz] = dp[0][j][l];
        if (tot != MAX) {
          if (j + 1 <= k)
            dp[1][j + 1][1] = min(dp[1][j + 1][1], {tot, a});
          if (a > siz) {
            tot += (a - siz) * l;
            siz = a;
          } else
            tot += siz - a;
          if (l + 1 <= n)
            dp[1][j][l + 1] = min(dp[1][j][l + 1], {tot, siz});
        }
      }
    }
    for (I j = 0; j <= k; j++) {
      copy_n(dp[1][j], n + 1, dp[0][j]);
      fill_n(dp[1][j], n + 1, pair<I, I>{MAX, 0});
    }
  }
  I res = MAX;
  for (I i = 0; i <= k; i++)
    for (I j = 0; j <= n; j++)
      res = min(res, dp[0][i][j].first);
  printf("%i\n", res);
  return 0;
}