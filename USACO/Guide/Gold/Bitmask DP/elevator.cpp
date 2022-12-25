#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 20;
const Lli MAX = 1e18;

// 1. current ride
// 2. people transported
Lli dp[N + 1][1 << N];
I w_arr[N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(Lli), MAX);
  I n, x;
  cin >> n >> x;
  for (I i = 0; i < n; i++)
    cin >> w_arr[i];
  dp[1][0] = 0;
  for (I i = 1; i <= n; i++) {
    for (I j = 0; j < (1 << n); j++) {
      if (dp[i][j] != MAX) {
        if (j == (1 << n) - 1) {
          printf("%i\n", i);
          return 0;
        }
        for (I k = 0; k < n; k++) {
          if (!(j >> k & 1)) {
            if (dp[i][j] + w_arr[k] <= x)
              dp[i][j | 1 << k] = min(dp[i][j | 1 << k], dp[i][j] + w_arr[k]);
            else
              dp[i + 1][j] = 0;
          }
        }
      }
    }
  }
  return 0;
}