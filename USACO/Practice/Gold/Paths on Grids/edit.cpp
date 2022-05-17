#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using S = string;

const I N = 5000;
const I M = 5000;

I dp[N + 1][M + 1];

I main(void) {
#ifdef ETHANKIM8683
  freopen("edit.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  S a_str, b_str;
  cin >> a_str;
  cin >> b_str;
  const I n = a_str.length();
  const I m = b_str.length();
  for (I i = 0; i < n + 1; i++)
    fill_n(dp[i], m + 1, 1e9);
  dp[0][0] = 0;
  for (I i = 0; i <= n; i++) {
    for (I j = 0; j <= m; j++) {
      if (i < n && j < m && a_str[i] == b_str[j]) {
        // proceed to next char
        dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j]);
        // add to a_str
        if (j + 2 <= m)
          dp[i + 1][j + 2] = min(dp[i + 1][j + 2], dp[i][j] + 1);
        // add to b_str
        if (i + 2 <= n)
          dp[i + 2][j + 1] = min(dp[i + 2][j + 1], dp[i][j] + 1);
      } else {
        // remove from a_str
        if (i + 1 <= n)
          dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
        // remove from b_str
        if (j + 1 <= m)
          dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + 1);
        // replace current char of a_str/b_str
        if (i + 1 <= n && j + 1 <= m)
          dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + 1);
      }
    }
  }
  printf("%i\n", dp[n][m]);
  return 0;
}