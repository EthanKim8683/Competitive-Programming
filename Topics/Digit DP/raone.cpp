#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;

const I L = 9;
const I K = 9 * 4 + 1;

// 1. current index
// 2. eve(x) - odd(x) + K
// 3. low < x < upp, low = x < upp, low < x = upp, low = x = upp
I dp[L + 1][K + K + 1][4];
vector<I> low_dgts;
vector<I> upp_dgts;

I slv(I low, I upp) {
  fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(I), 0);
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
  dp[0][K][3] = 1;
  for (I i = 0; i < len; i++) {
    for (I j = 0; j <= K + K; j++) {
      for (I k = 0; k < 4; k++) {
        const I beg = k >> 1 & 1 ? low_dgts[i] : 0;
        const I end = k >> 0 & 1 ? upp_dgts[i] : 9;
        for (I l = beg; l <= end; l++) {
          const I msk = (k >> 1 & 1 ? l == low_dgts[i] : 0) << 1 |
                        (k >> 0 & 1 ? l == upp_dgts[i] : 0) << 0;
          const I sum = (len - i) % 2 ? j - l : j + l;
          if (sum >= 0 && sum <= K + K)
            dp[i + 1][sum][msk] += dp[i][j][k];
        }
      }
    }
  }
  I res = 0;
  for (I i = 0; i < 4; i++)
    res += dp[len][K + 1][i];
  return res;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I a, b;
    cin >> a >> b;
    printf("%i\n", slv(a, b));
  }
  return 0;
}