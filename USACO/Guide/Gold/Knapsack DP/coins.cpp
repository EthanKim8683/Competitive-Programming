#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using U = unsigned;

U cs[100];
U dp[1000001];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("coins.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, x;
  cin >> n >> x;
  for (U i = n; i--;)
    cin >> cs[i];
  fill_n(dp, x + 1, 1e9);
  dp[0] = 0;
  for (U i = 0; i <= x; i++) {
    const auto count = dp[i] + 1;
    for (U j = n; j--;) {
      const U k = i + cs[j];
      if (k <= x)
        dp[k] = min(dp[k], count);
    }
  }
  const auto result = dp[x];
  if (result == 1e9)
    printf("-1\n");
  else
    printf("%u\n", result);
  return 0;
}