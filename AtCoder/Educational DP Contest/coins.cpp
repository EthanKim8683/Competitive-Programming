#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lf = long double;

const I N = 2999;

Lf p_arr[N];
Lf dp[N + 1][N + 1];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> p_arr[i];
  dp[0][0] = 1;
  for (I i = 0; i < n; i++) {
    for (I j = 0; j <= i; j++) {
      dp[i + 1][j + 1] += dp[i][j] * p_arr[i];
      dp[i + 1][j] += dp[i][j] * (1 - p_arr[i]);
    }
  }
  Lf res = 0;
  for (I i = n - n / 2; i <= n; i++)
    res += dp[n][i];
  printf("%.10Lf\n", res);
  return 0;
}