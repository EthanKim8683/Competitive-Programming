#include <iostream>
#include <cstdio>

using namespace std;

using I = int;

const I N = 1e5;

I acts[N][3];
I dp[N + 1][3];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    for (I j = 0; j < 3; j++)
      cin >> acts[i][j];
  for (I i = 0; i < 3; i++)
    dp[1][i] = acts[0][i];
  for (I i = 1; i < n; i++)
    for (I j = 0; j < 3; j++)
      for (I k = 0; k < 3; k++)
        if (j != k)
          dp[i + 1][k] = max(dp[i + 1][k], dp[i][j] + acts[i][k]);
  I res = 0;
  for (I i = 0; i < 3; i++)
    res = max(res, dp[n][i]);
  printf("%i\n", res);
  return 0;
}