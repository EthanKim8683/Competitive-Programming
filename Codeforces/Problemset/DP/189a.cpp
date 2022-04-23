#include <iostream>
#include <cstdio>
#include <algorithm>

#define N 4000

using namespace std;

using I = int;

I dp[N + 1];

I main(void) {
#ifdef ETHANKIM8683
  freopen("189a.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, a, b, c;
  cin >> n >> a >> b >> c;
  fill_n(dp, n + 1, -1);
  dp[0] = 0;
  for (I i = 0; i < n; i++) {
    if (dp[i] != -1) {
      if (i + a <= n)
        dp[i + a] = max(dp[i + a], dp[i] + 1);
      if (i + b <= n)
        dp[i + b] = max(dp[i + b], dp[i] + 1);
      if (i + c <= n)
        dp[i + c] = max(dp[i + c], dp[i] + 1);
    }
  }
  printf("%i\n", dp[n]);
  return 0;
}