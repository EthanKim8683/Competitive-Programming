#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I M = 10;
const I N = 10;

// 1. length
// 2. last digit
I dp[N + 1][M];
I dgts[M];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  for (I i = 1; i <= t; i++) {
    I m, n;
    cin >> m >> n;
    fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(I), 0);
    for (I j = 0; j < m; j++) {
      I dgt;
      cin >> dgt;
      dgts[j] = dgt;
      dp[1][j] = 1;
    }
    for (I j = 1; j < n; j++)
      for (I k = 0; k < m; k++)
        if (dp[j][k] > 0)
          for (I l = 0; l < m; l++)
            if (abs(dgts[k] - dgts[l]) <= 2)
              dp[j + 1][l] += dp[j][k];
    I res = 0;
    for (I j = 0; j < m; j++)
      res += dp[n][j];
    printf("Case %i: %i\n", i, res);
  }
  return 0;
}