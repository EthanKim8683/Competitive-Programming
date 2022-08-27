#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 100;
const I K = 1e5;
const Lli MOD = 1e9 + 7;

I a_arr[N];
Lli dp[N + 1][K + 1];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, k;
  cin >> n >> k;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  dp[0][0] = 1;
  for (I i = 0; i < n; i++) {
    Lli tot = 0;
    for (I j = 0; j <= k; j++) {
      (tot += dp[i][j]) %= MOD;
      (dp[i + 1][j] += tot) %= MOD;
      if (j - a_arr[i] >= 0)
        (tot -= dp[i][j - a_arr[i]]) %= MOD;
    }
  }
  printf("%lli\n", dp[n][k] + (dp[n][k] < 0) * MOD);
  return 0;
}