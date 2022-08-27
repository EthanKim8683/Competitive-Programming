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
// 3. x < upp, x = upp
I dp[L + 1][K + 1][2];
vector<I> dgts;

void tod(I val) {
  dgts.clear();
  for (; val; val /= 10)
    dgts.push_back(val % 10);
  reverse(dgts.begin(), dgts.end());
}

I slv(I upp, I trg, I cnt) {
  fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(I), 0);
  tod(upp);
  const I len = dgts.size();
  dp[0][0][1] = 1;
  for (I i = 0; i < len; i++) {
    for (I j = 0; j <= cnt; j++) {
      for (I k = 0; k < 2; k++) {
        const I beg = 0;
        const I end = k >> 0 & 1 ? dgts[i] : 9;
        for (I l = beg; l <= end; l++) {
          const I msk = (k >> 0 & 1 ? l == dgts[i] : 0) << 0;
          dp[i + 1][j + (l == trg)][msk] += dp[i][j][k];
        }
      }
    }
  }
  I res = 0;
  for (I i = 0; i < 2; i++)
    res += dp[len][cnt][i];
  return res;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I a, b, d, k;
  cin >> a >> b >> d >> k;
  printf("%i\n", slv(b, d, k) - slv(a - 1, d, k));
  return 0;
}