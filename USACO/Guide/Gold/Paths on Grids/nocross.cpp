#include <iostream>
#include <cstdio>

using namespace std;

using I = int;

const I N = 1000;

I dp[N + 1][N + 1];
I a_arr[N];
I b_arr[N];

I main(void) {
  freopen("nocross.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("nocross.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  for (I i = 0; i < n; i++)
    cin >> b_arr[i];
  for (I i = 0; i <= n; i++) {
    for (I j = 0; j <= n; j++) {
      if (i < n && j < n && abs(a_arr[i] - b_arr[j]) <= 4)
        dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + 1);
      if (i + 1 <= n)
        dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
      if (j + 1 <= n)
        dp[i][j + 1] = max(dp[i][j + 1], dp[i][j]);
    }
  }
  printf("%i\n", dp[n][n]);
  return 0;
}