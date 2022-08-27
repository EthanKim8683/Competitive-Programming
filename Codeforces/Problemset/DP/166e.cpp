#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MOD = 1e9 + 7;

Lli dp[2][4];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  I cur = 0;
  dp[cur][0] = 1;
  for (I i = 0; i < n; i++) {
    for (I j = 0; j < 4; j++) {
      for (I k = 0; k < 4; k++)
        if (k != j)
          (dp[!cur][k] += dp[cur][j]) %= MOD;
      dp[cur][j] = 0;
    }
    cur ^= 1;
  }
  printf("%lli\n", dp[cur][0]);
  return 0;
}