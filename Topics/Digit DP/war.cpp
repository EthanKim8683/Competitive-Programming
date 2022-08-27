#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;
using B = bool;
using Lli = long long int;

const I L = 13;
const I C = 2520;

// 1. current index
// 2. x % lcm(1 ... 9)
// 3. visited digits
// 4. low < x < upp, low = x < upp, low < x = upp, low = x = upp
Lli dp[L + 1][C][1 << 9][4];
Lli pows[10];
vector<I> low_dgts;
vector<I> upp_dgts;

Lli pow(Lli bse, Lli exp) {
  Lli res = 1;
  while (exp) {
    if (exp & 1)
      (res *= bse) %= C;
    (bse *= bse) %= C;
    exp >>= 1;
  }
  return res;
}

void tod(Lli low, Lli upp) {
  low_dgts.clear();
  upp_dgts.clear();
  for (; low || upp; low /= 10, upp /= 10) {
    low_dgts.push_back(low % 10);
    upp_dgts.push_back(upp % 10);
  }
  reverse(low_dgts.begin(), low_dgts.end());
  reverse(upp_dgts.begin(), upp_dgts.end());
}

Lli slv(Lli low, Lli upp) {
  fill(&dp[0][0][0][0], &dp[0][0][0][0] + sizeof(dp) / sizeof(Lli), 0);
  tod(low, upp);
  const I len = low_dgts.size();
  dp[0][0][0][3] = 1;
  for (I i = 0; i < len; i++) {
    for (I j = 0; j < C; j++) {
      for (I k = 0; k < (1 << 9); k++) {
        for (I l = 0; l < 4; l++) {
          if (dp[i][j][k][l] > 0) {
            const I beg = l >> 0 & 1 ? low_dgts[i] : 0;
            const I end = l >> 1 & 1 ? upp_dgts[i] : 9;
            for (I m = beg; m <= end; m++) {
              const I msk = (l >> 0 & 1 ? m == low_dgts[i] : 0) << 0 |
                            (l >> 1 & 1 ? m == upp_dgts[i] : 0) << 1;
              dp[i + 1][(j + pows[m]) % C][m == 0 ? k : k | 1 << (m - 1)][msk] += dp[i][j][k][l];
            }
          }
        }
      }
    }
  }
  Lli res = 0;
  for (I i = 0; i < C; i++) {
    for (I j = 0; j < (1 << 9); j++) {
      B spc = true;
      for (I k = 1; k <= 9 && spc; k++)
        if (j >> (k - 1) & 1)
          spc &= i % k == 0;
      if (spc)
        for (I k = 0; k < 4; k++)
          res += dp[len][i][j][k];
    }
  }
  return res;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  for (I i = 1; i < 10; i++)
    pows[i] = pow(i, i);
  I q;
  cin >> q;
  while (q--) {
    Lli l, r;
    cin >> l >> r;
    printf("%lli\n", slv(l, r));
  }
  return 0;
}