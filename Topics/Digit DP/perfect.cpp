#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;

const I L = 8;
const I K = 10;

// 1. current index
// 2. digit sum
// 3. x < upp, x = upp
I dp[L + 1][K + 1][2];
vector<I> dgts;

void tod(I val) {
  dgts.clear();
  for (; val; val /= 10)
    dgts.push_back(val % 10);
  reverse(dgts.begin(), dgts.end());
}

I slv(I upp) {
  fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(I), 0);
  tod(upp);
  const I len = dgts.size();
  dp[0][0][1] = 1;
  for (I i = 0; i < len; i++) {
    for (I j = 0; j <= K; j++) {
      for (I k = 0; k < 2; k++) {
        const I beg = 0;
        const I end = k >> 0 & 1 ? dgts[i] : 9;
        for (I l = beg; l <= end; l++) {
          if (j + l <= K) {
            const I msk = (k >> 0 & 1 ? l == dgts[i] : 0) << 0;
            dp[i + 1][j + l][msk] += dp[i][j][k];
          }
        }
      }
    }
  }
  I res = 0;
  for (I i = 0; i < 2; i++)
    res += dp[len][K][i];
  return res;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I k;
  cin >> k;
  I l = 19;
  I r = 10800100;
  while (l < r) {
    const I m = l + (r - l) / 2;
    if (slv(m) >= k)
      r = m;
    else
      l = m + 1;
  }
  printf("%i\n", l);
  return 0;
}