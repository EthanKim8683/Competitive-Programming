#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MOD = 1e9 + 7;
const I N = 1e5;
const I M = 100;

I x_arr[N];
Lli dp[N + 1][M + 1];

I main(void) {
#ifdef ETHANKIM8683
  freopen("array.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  for (I i = 0; i < n; i++)
    cin >> x_arr[i];
  const auto x = x_arr[0];
  if (x)
    dp[0][x] = 1;
  else
    for (I i = 1; i <= m; i++)
      dp[1][i] = 1;
  for (I i = 0; i < n; i++) {
    const auto x = x_arr[i];
    if (x) {
      dp[i + 1][x] = (dp[i + 1][x] + dp[i][x]) % MOD;
      if (x - 1 >= 1)
        dp[i + 1][x] = (dp[i + 1][x] + dp[i][x - 1]) % MOD;
      if (x + 1 <= m)
        dp[i + 1][x] = (dp[i + 1][x] + dp[i][x + 1]) % MOD;
    } else {
      for (I j = 1; j <= m; j++) {
        dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % MOD;
        if (j - 1 >= 1)
          dp[i + 1][j - 1] = (dp[i + 1][j - 1] + dp[i][j]) % MOD;
        if (j + 1 <= m)
          dp[i + 1][j + 1] = (dp[i + 1][j + 1] + dp[i][j]) % MOD;
      }
    }
  }
  Lli res = 0;
  for (I i = 1; i <= m; i++)
    res = (res + dp[n][i]) % MOD;
  printf("%lli\n", res);
  return 0;
}