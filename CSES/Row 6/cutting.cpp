// start 9:51
// end 10:00
// tries 1

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I A = 500;
const I B = 500;
const I MAX = 1e9;

I dp[A + 1][B + 1];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(I), MAX);
  I a, b;
  cin >> a >> b;
  for (I i = 1; i <= min(a, b); i++)
    dp[i][i] = 0;
  for (I i = 1; i <= a; i++) {
    for (I j = 1; j <= b; j++) {
      for (I k = 1; k <= i && i + k <= a; k++)
        dp[i + k][j] = min(dp[i + k][j], dp[i][j] + dp[k][j] + 1);
      for (I k = 1; k <= j && j + k <= b; k++)
        dp[i][j + k] = min(dp[i][j + k], dp[i][j] + dp[i][k] + 1);
    }
  }
  printf("%i\n", dp[a][b]);
  return 0;
}