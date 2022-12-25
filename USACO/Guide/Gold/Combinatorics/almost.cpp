#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 1000;

Lli dp[N + 1][N + 1];

I main(void) {
#ifdef ETHANKIM8683
  freopen("almost.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, k;
  cin >> n >> k;
  dp[0][0] = 1;
  dp[1][0] = 0;
  dp[2][0] = 1;
  for (I i = 3; i <= n; i++)
    dp[i][0] = (i - 1) * (dp[i - 1][0] + dp[i - 2][0]);
  for (I i = 1; i <= n; i++)
    for (I j = 1; j <= n; j++)
      dp[i][j] = dp[i - 1][j - 1] * i / j;
  Lli res = 0;
  for (I i = n - k; i <= n; i++)
    res += dp[n][i];
  printf("%lli\n", res);
  return 0;
}