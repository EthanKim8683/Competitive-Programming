#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 1e4;
const I K = 1e3;

I s_arr[N];
pair<I, I> dp[N + 1][K + 1];

I main(void) {
  freopen("teamwork.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("teamwork.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, k;
  cin >> n >> k;
  for (I i = 0; i < n; i++)
    cin >> s_arr[i];
  for (I i = n; i--;)
    fill_n(dp[i], k + 1, pair<I, I>{-1, -1});
  dp[0][0] = {0, 0};
  for (I i = 0; i < n; i++) {
    const auto s = s_arr[i];
    for (I j = 0; j <= k; j++) {
      if (dp[i][j].first != -1) {
        const auto [tot, cur] = dp[i][j];
        if (j + 1 <= k)
          dp[i + 1][j + 1] = {tot, max(cur, s)};
        const I end = tot + cur * j;
        if (end > dp[i + 1][1].first)
          dp[i + 1][1] = {end, s};
      }
    }
  }
  I res = 0;
  for (I i = 1; i <= k; i++) {
    const auto [tot, cur] = dp[n][i];
    res = max(res, tot + cur * i);
  }
  printf("%i\n", res);
  return 0;
}