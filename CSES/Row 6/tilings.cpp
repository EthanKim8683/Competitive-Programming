#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 10;
const I M = 1000;
const Lli MOD = 1e9 + 7;

Lli dp0[M + 1][1 << N];
vector<I> dp1[N + 1];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  dp0[0][0] = 1;
  for (I i = 0; i < m; i++) {
    for (I j = 0; j < (1 << n); j++) {
      if (dp0[i][j] > 0) {
        for (I k = 0; k <= n; k++)
          dp1[k].clear();
        dp1[0].push_back(0);
        for (I k = 0; k < n; k++) {
          for (const auto msk : dp1[k]) {
            if ((j >> k & 1) == 0) {
              if (k + 1 <= n)
                dp1[k + 1].push_back(msk | (1 << k));
              if (k + 2 <= n && (j >> (k + 1) & 1) == 0)
                dp1[k + 2].push_back(msk);
            } else
              dp1[k + 1].push_back(msk);
          }
        }
        for (const auto msk : dp1[n])
          (dp0[i + 1][msk] += dp0[i][j]) %= MOD;
      }
    }
  }
  printf("%lli\n", dp0[m][0]);
  return 0;
}