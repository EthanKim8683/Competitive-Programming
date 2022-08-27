#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 5000;
const I M = 5000;
const I K = 5000;

Lli dp[N + 1][K + 1];
Lli ps[N + 1];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, m, k;
  cin >> n >> m >> k;
  for (I i = 1; i <= n; i++)
    cin >> ps[i];
  for (I i = 1; i < n; i++)
    ps[i + 1] += ps[i];
  Lli res = 0;
  for (I i = 0; i <= n; i++) {
    for (I j = 0; j <= k; j++) {
      res = max(res, dp[i][j]);
      if (i + m <= n && j + 1 <= k)
        dp[i + m][j + 1] = max(dp[i + m][j + 1], dp[i][j] + ps[i + m] - ps[i]);
      if (i + 1 <= n)
        dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
    }
  }
  printf("%lli\n", res);
  return 0;
}
