#include <iostream>
#include <cstdio>

using namespace std;

using I = int;

const I W = 600;
const I H = 600;

I dp[W + 1][H + 1];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I w, h;
  cin >> w >> h;
  I n;
  cin >> n;
  for (I i = 1; i <= w; i++)
    for (I j = 1; j <= h; j++)
      dp[i][j] = i * j;
  for (I i = 0; i < n; i++) {
    I w_i, h_i;
    cin >> w_i >> h_i;
    dp[w_i][h_i] = 0;
  }
  for (I i = 1; i <= w; i++) {
    for (I j = 1; j <= h; j++) {
      if (dp[i][j] != i * j) {
        for (I k = 1; k <= i && i + k <= w; k++)
          dp[i + k][j] = min(dp[i + k][j], dp[i][j] + dp[k][j]);
        for (I k = 1; k <= j && j + k <= h; k++)
          dp[i][j + k] = min(dp[i][j + k], dp[i][j] + dp[i][k]);
      }
    }
  }
  printf("%i\n", dp[w][h]);
  return 0;
}