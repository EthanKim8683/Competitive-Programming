#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;
using B = bool;

const I L = 10;
const I K = 9 * 5;

// 1. current index
// 2. eve(x) - odd(x) + K
// 3. low < x < upp, low = x < upp, low < x = upp, low = x = upp
I dp[L + 1][K + K + 1][4];
vector<I> low_dgts;
vector<I> upp_dgts;
B coms[K + 1];
vector<I> prms;

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
    for (const auto prm : prms)
      res += dp[len][K + prm][i];
  return res;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  coms[0] = true;
  coms[1] = true;
  for (I i = 2; i * i <= K; i++)
    if (!coms[i])
      for (I j = i * i; j <= K; j += i)
        coms[j] = true;
  for (I i = 0; i <= K; i++)
    if (!coms[i])
      prms.push_back(i);
  I t;
  cin >> t;
  while (t--) {
    I a, b;
    cin >> a >> b;
    printf("%i\n", slv(a, b));
  }
  return 0;
}