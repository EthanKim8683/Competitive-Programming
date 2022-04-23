#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using U = unsigned;
using I = int;

I h[100000];
U dp[100000];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("frog.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  fill_n(dp, n, 1e9);
  for (U i = 0; i < n; i++)
    cin >> h[i];
  dp[0] = 0;
  for (U i = 0; i < n; i++) {
    const auto i_dp = dp[i];
    const auto i_h = h[i];
    const U j = i + 1;
    if (j < n) {
      dp[j] = min(dp[j], i_dp + abs(i_h - h[j]));
      const U k = i + 2;
      if (k < n)
        dp[k] = min(dp[k], i_dp + abs(i_h - h[k]));
    }
  }
  printf("%u\n", dp[n - 1]);
  return 0;
}