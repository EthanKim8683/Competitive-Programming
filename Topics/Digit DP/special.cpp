#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;
using Lli = long long int;

const I L = 19;
const I C = 2520;

// 1. current index
// 2. x % lcm(1 ... 9)
// 6. visited digits
// 7. low < x < upp, low = x < upp, low < x = upp, low = x = upp
Lli dp[L + 1][C][1 << 9][4];
vector<I> low_dgts;
vector<I> upp_dgts;

Lli slv(Lli low, Lli upp, I spc) {
  fill(&dp[0][0][0][0], &dp[0][0][0][0] + sizeof(dp) / sizeof(Lli), 0);
  low_dgts.clear();
  upp_dgts.clear();
  while (low || upp) {
    low_dgts.push_back(low % 10);
    upp_dgts.push_back(upp % 10);
    low /= 10;
    upp /= 10;
  }
  const I len = low_dgts.size();
  reverse(low_dgts.begin(), low_dgts.end());
  reverse(upp_dgts.begin(), upp_dgts.end());
  for (I i = low_dgts[0]; i <= upp_dgts[0]; i++) {
    const I msk = (i == low_dgts[0]) << 0 |
                  (i == upp_dgts[0]) << 1;
    dp[1][i][i == 0 ? 0 : 1 << (i - 1)][msk]++;
  }
  for (I i = 1; i < len; i++) {
    for (I j = 0; j < C; j++) {
      for (I k = 0; k < (1 << 9); k++) {
        for (I l = 0; l < 4; l++) {
          if (dp[i][j][k][l] > 0) {
            const I beg = l >> 0 & 1 ? low_dgts[i] : 0;
            const I end = l >> 1 & 1 ? upp_dgts[i] : 9;
            for (I m = beg; m <= end; m++) {
              const I msk = (l >> 0 & 1 ? m == low_dgts[i] : 0) << 0 |
                            (l >> 1 & 1 ? m == upp_dgts[i] : 0) << 1;
              dp[i + 1][(j * 10 + m) % C][m == 0 ? k : k | 1 << (m - 1)][msk] += dp[i][j][k][l];
            }
          }
        }
      }
    }
  }
  Lli res = 0;
  for (I i = 0; i < C; i++) {
    for (I j = 0; j < (1 << 9); j++) {
      if (__builtin_popcount(j & (
          1            << 0 | (i % 2 == 0) << 1 | (i % 3 == 0) << 2 |
          (i % 4 == 0) << 3 | (i % 5 == 0) << 4 | (i % 6 == 0) << 5 |
          (i % 7 == 0) << 6 | (i % 8 == 0) << 7 | (i % 9 == 0) << 8)) >= spc)
        for (I k = 0; k < 4; k++)
          res += dp[len][i][j][k];
    }
  }
  return res;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I q;
  cin >> q;
  while (q--) {
    Lli l, r;
    I k;
    cin >> l >> r >> k;
    printf("%lli\n", slv(l, r, k));
  }
  return 0;
}