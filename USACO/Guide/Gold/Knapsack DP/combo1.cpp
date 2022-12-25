#include <iostream>
#include <cstdio>

#define MOD 1000000007

using namespace std;

using U = unsigned;
using Llu = long long unsigned;

U cs[100];
Llu dp[1000001];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("combo1.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, x;
  cin >> n >> x;
  for (U i = n; i--;)
    cin >> cs[i];
  dp[0] = 1;
  for (U i = 0; i < x; i++) {
    const auto count = dp[i];
    if (count) {
      for (U j = n; j--;) {
        const U k = i + cs[j];
        if (k <= x)
          dp[k] = (dp[k] + count) % MOD;
      }
    }
  }
  printf("%llu\n", dp[x]);
  return 0;
}