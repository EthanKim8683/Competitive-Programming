#include <iostream>
#include <cstdio>

using namespace std;

using I = int;

const I N = 100;
const I K = 10;
const I MOD = 1e8;

I dp[N + 1][N + 1][K + 1][K + 1];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n1, n2, k1, k2;
  cin >> n1 >> n2 >> k1 >> k2;
  dp[0][0][0][0] = 1;
  for (I i = 0; i <= n1; i++) {
    for (I j = 0; j <= n2; j++) {
      for (I k = 0; k <= k1; k++) {
        for (I l = 0; l <= k2; l++) {
          if (i + 1 <= n1 && k + 1 <= k1)
            dp[i + 1][j][k + 1][0] = (dp[i + 1][j][k + 1][0] + dp[i][j][k][l]) % MOD;
          if (j + 1 <= n2 && l + 1 <= k2)
            dp[i][j + 1][0][l + 1] = (dp[i][j + 1][0][l + 1] + dp[i][j][k][l]) % MOD;
        }
      }
    }
  }
  I res = 0;
  for (I i = 0; i <= k1; i++)
    for (I j = 0; j <= k2; j++)
      res = (res + dp[n1][n2][i][j]) % MOD;
  printf("%i\n", res);
  return 0;
}