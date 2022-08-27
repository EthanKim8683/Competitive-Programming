#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;

const I N = 20;
const I MAX = 1e9;
const I MIN = -1e9;

vector<I> begs[N];
I durs[N];
I dp[1 << N];

I main(void) {
#ifndef ETHANKIM8683
  freopen("movie.in", "r", stdin);
  freopen("movie.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, l;
  cin >> n >> l;
  fill_n(dp, 1 << n, MIN);
  for (I i = 0; i < n; i++) {
    I d, c;
    cin >> d >> c;
    durs[i] = d;
    for (I j = 0; j < c; j++) {
      I beg;
      cin >> beg;
      begs[i].push_back(beg);
    }
  }
  I res = MAX;
  dp[0] = 0;
  for (I i = 0; i < (1 << n); i++) {
    if (dp[i] != MIN) {
      if (dp[i] >= l)
        res = min(res, __builtin_popcount(i));
      for (I j = 0; j < n; j++) {
        if (!(i >> j & 1)) {
          const I k = upper_bound(begs[j].begin(), begs[j].end(), dp[i]) - begs[j].begin() - 1;
          if (k >= 0) {
            const I beg = begs[j][k];
            const I end = beg + durs[j];
            if (beg <= dp[i] && end > dp[i])
              dp[i | 1 << j] = max(dp[i | 1 << j], end);
          }
        }
      }
    }
  }
  if (res != MAX)
    printf("%i\n", res);
  else
    printf("-1\n");
  return 0;
}