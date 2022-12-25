#include <iostream>
#include <cstdio>
#include <algorithm>
#include <tuple>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 100000;
const Lli S = 2000;

tuple<Lli, Lli, Lli> items[N];
Lli dp[S + 1];

I main(void) {
#ifdef ETHANKIM8683
  freopen("knapsack.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  Lli s, n;
  cin >> s >> n;
  for (I i = n; i--;) {
    auto& [v, w, k] = items[i];
    cin >> v >> w >> k;
  }
  sort(items, items + n);
  for (I i = n; i--;) {
    const auto [v, w, k] = items[i];
    for (Lli j = s; j--;) {
      const auto cur = dp[j];
      for (Lli l = 1; l <= k && j + l * w <= s && cur + l * v > dp[j + l * w]; l++)
        dp[j + l * w] = cur + l * v;
    }
  }
  printf("%lli\n", dp[s]);
  return 0;
}