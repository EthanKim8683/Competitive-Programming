#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using U = unsigned;

U as[200000];
U a_dp[200001];
U b_dp[200001];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("tower.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U t;
  cin >> t;
  while (t--) {
    U n;
    cin >> n;
    const U x = n + 1;
    fill_n(a_dp, x, 1e9);
    fill_n(b_dp, x, 1e9);
    for (U i = 0; i < n; i++)
      cin >> as[i];
    a_dp[0] = 0;
    for (U i = 0; i < n; i++) {
      const auto i_b_dp = b_dp[i];
      const auto i_a_dp = a_dp[i];
      const U j = i + 1;
      const U k = i + 2;
      U a = as[i];
      a_dp[j] = min(a_dp[j], i_b_dp);
      b_dp[j] = min(b_dp[j], i_a_dp + a);
      if (k <= n) {
        a += as[j];
        a_dp[k] = min(a_dp[k], i_b_dp);
        b_dp[k] = min(b_dp[k], i_a_dp + a);
      }
    }
    printf("%u\n", min(a_dp[n], b_dp[n]));
  }
  return 0;
}