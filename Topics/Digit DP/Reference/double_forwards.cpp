#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;

const I L = 10;
const I K = 9;

// 1. current index
// 2. trg count
// 3. low < x < upp, low = x < upp, low < x = upp, low = x = upp
I dp[L + 1][K + 1][4];
vector<I> low_dgts;
vector<I> upp_dgts;

void tod(I low, I upp) {
  low_dgts.clear();
  upp_dgts.clear();
  for (; low || upp; low /= 10, upp /= 10) {
    low_dgts.push_back(low % 10);
    upp_dgts.push_back(upp % 10);
  }
  reverse(low_dgts.begin(), low_dgts.end());
  reverse(upp_dgts.begin(), upp_dgts.end());
}

I slv(I low, I upp, I trg, I cnt) {
  fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(I), 0);
  tod(low, upp);
  const I len = low_dgts.size();
  dp[0][0][3] = 1;
  for (I i = 0; i < len; i++) {
    for (I j = 0; j <= cnt; j++) {
      for (I k = 0; k < 4; k++) {
        const I beg = k >> 1 & 1 ? low_dgts[i] : 0;
        const I end = k >> 0 & 1 ? upp_dgts[i] : 9;
        for (I l = beg; l <= end; l++) {
          const I msk = (k >> 1 & 1 ? l == low_dgts[i] : 0) << 1 |
                        (k >> 0 & 1 ? l == upp_dgts[i] : 0) << 0;
          dp[i + 1][j + (l == trg)][msk] += dp[i][j][k];
        }
      }
    }
  }
  I res = 0;
  for (I i = 0; i < 4; i++)
    res += dp[len][cnt][i];
  return res;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I a, b, d, k;
  cin >> a >> b >> d >> k;
  printf("%i\n", slv(a, b, d, k));
  return 0;
}