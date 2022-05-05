#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MOD = 1e9 + 7;
const I N = 100;

Lli dp[N + 1][N + 1][2];

I main(void) {
#ifdef ETHANKIM8683
  freopen("431c.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, k, d;
  cin >> n >> k >> d;
  dp[0][0][0] = 1;
  for (I i = 0; i < n; i++) {
    for (I j = 0; j < n; j++) {
      for (I l = 1; l <= k; l++) {
        if (j + l <= n) {
          auto& a = dp[i + 1][j + l][l >= d];
          auto& b = dp[i + 1][j + l][1];
          a = (a + dp[i][j][0]) % MOD;
          b = (b + dp[i][j][1]) % MOD;
        }
      }
    }
  }
  Lli res = 0;
  for (I i = 0; i <= n; i++)
    res = (res + dp[i][n][1]) % MOD;
  printf("%lli\n", res);
  return 0;
}