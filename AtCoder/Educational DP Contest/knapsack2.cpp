#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 100;
const I V = 1e5;
const Lli MAX = 1e18;

pair<I, I> itms[N];
Lli dp[V + 1];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, w;
  cin >> n >> w;
  fill_n(dp, V + 1, MAX);
  for (I i = 0; i < n; i++) {
    I wi, vi;
    cin >> wi >> vi;
    itms[i] = {wi, vi};
  }
  dp[0] = 0;
  for (I i = 0; i < n; i++) {
    const auto [wi, vi] = itms[i];
    for (I j = V; j >= 0; j--)
      if (dp[j] != MAX && dp[j] + wi <= w)
        dp[j + vi] = min(dp[j + vi], dp[j] + wi);
  }
  for (I i = V; i >= 0; i--) {
    if (dp[i] != MAX) {
      printf("%i\n", i);
      break;
    }
  }
  return 0;
}