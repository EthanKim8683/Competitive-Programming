#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 200;
const I K = 200;

Lli a_arr[N];
I dp[K][K * 64];

I main(void) {
#ifdef ETHANKIM8683
  freopen("round.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, k;
  cin >> n >> k;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  for (I i = 0; i < k; i++)
    fill_n(dp[i], k * 64, -1);
  dp[0][0] = 0;
  I res = 0;
  for (I i = 0; i < n; i++) {
    auto a = a_arr[i];
    I t_cnt = 0;
    I f_cnt = 0;
    while (a % 2 == 0) {
      a /= 2;
      t_cnt++;
    }
    while (a % 5 == 0) {
      a /= 5;
      f_cnt++;
    }
    for (I j = k - 1; j >= 0; j--) {
      for (I t = k * 64 - 1; t >= 0; t--) {
        const auto f = dp[j][t];
        if (f != -1) {
          // multiply
          const I t_tot = t + t_cnt;
          const I f_tot = f + f_cnt;
          if (j + 1 < k && t_tot < k * 64) {
            auto& a = dp[j + 1][t_tot];
            a = max(a, f_tot);
          }
          res = max(res, min(t_tot, f_tot));
          // don't multiply (do nothing)
        }
      }
    }
  }
  printf("%i\n", res);
  return 0;
}