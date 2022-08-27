#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 100;
const I W = 1e5;

pair<I, I> itms[N];
Lli dp[W + 1];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, w;
  cin >> n >> w;
  for (I i = 0; i < n; i++) {
    I wi, vi;
    cin >> wi >> vi;
    itms[i] = {wi, vi};
  }
  for (I i = 0; i < n; i++) {
    const auto [wi, vi] = itms[i];
    for (I j = w; j >= 0; j--)
      if (j + wi <= w)
        dp[j + wi] = max(dp[j + wi], dp[j] + vi);
  }
  printf("%lli\n", dp[w]);
  return 0;
}