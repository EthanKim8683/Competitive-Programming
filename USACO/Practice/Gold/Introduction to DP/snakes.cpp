#include <iostream>
#include <cstdio>
#include <tuple>
#include <algorithm>

using namespace std;

using I = int;

const I N = 400;
const I K = N - 1;

I a_arr[N];
tuple<I, I, I> dp[N + 1][K + 1];

I main(void) {
  freopen("snakes.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("snakes.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, k;
  cin >> n >> k;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  for (I i = 0; i <= n; i++)
    fill_n(dp[i], k + 1, tuple<I, I, I>{1e9, 0, 0});
  dp[0][0] = {0, 0, 0};
  for (I i = 0; i < n; i++) {
    const auto a = a_arr[i];
    for (I j = 0; j <= k; j++) {
      auto [tot, siz, cnt] = dp[i][j];
      if (j + 1 <= k)
        dp[i + 1][j + 1] = {tot, a, 1};
      if (a > siz) {
        tot += cnt * (a - siz);
        siz = a;
      } else
        tot += siz - a;
      if (tot < get<0>(dp[i + 1][j]))
        dp[i + 1][j] = {tot, siz, cnt + 1};
    }
  }
  for (I i = 0; i <= n; i++) {
    for (I j = 0; j <= k; j++) {
      const auto [a, b, c] = dp[i][j];
      printf("%i %i %i\t\t", a, b, c);
    }
    printf("\n");
  }
  I res = 1e9;
  for (I i = 0; i <= k; i++)
    res = min(res, get<0>(dp[n][i]));
  printf("%i\n", res);
  return 0;
}