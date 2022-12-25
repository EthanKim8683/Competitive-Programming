#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 20;
const Lli MIN = -1e18;
const Lli MAX = 1e18;

pair<Lli, Lli> dp[1 << N];
Lli h_arr[N];
Lli w_arr[N];
Lli s_arr[N];

I main(void) {
  freopen("guard.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("guard.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, h;
  cin >> n >> h;
  for (I i = 0; i < n; i++)
    cin >> h_arr[i] >> w_arr[i] >> s_arr[i];
  fill_n(dp, 1 << n, pair<Lli, Lli>{0, 0});
  dp[0] = {0, MAX};
  Lli res = MIN;
  for (I i = 0; i < n; i++) {
    for (I j = (1 << n) - 1; j >= 0; j--) {
      if (__builtin_popcount(j) == i) {
        for (I k = 0; k < n; k++) {
          const Lli sft = min(dp[j].second - w_arr[k], s_arr[k]);
          if (~j & (1 << k) && sft > dp[j | (1 << k)].second)
            dp[j | (1 << k)] = {dp[j].first + h_arr[k], sft};
        }
        if (dp[j].first >= h)
          res = max(res, dp[j].second);
      }
    }
  }
  if (dp[(1 << n) - 1].first >= h)
    res = max(res, dp[(1 << n) - 1].second);
  if (res == MIN)
    printf("Mark is too tall\n");
  else
    printf("%lli\n", res);
  return 0;
}