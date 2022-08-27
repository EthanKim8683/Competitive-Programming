#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I L = 19;

vector<I> dgts;
Lli dp[L + 1][10][2];

void tod(Lli upp) {
  dgts.clear();
  for (; upp; upp /= 10)
    dgts.push_back(upp % 10);
  reverse(dgts.begin(), dgts.end());
}

Lli slv(Lli upp) {
  if (upp < 0)
    return 0;
  fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(Lli), 0);
  tod(upp);
  const I len = dgts.size();
  for (I i = 0; i < len; i++) {
    const I beg = 1;
    const I end = i == 0 ? dgts[i] : 9;
    for (I j = beg; j <= end; j++) {
      const I msk = (i == 0 ? j == dgts[i] : 0) << 0;
      dp[i + 1][j][msk] += 1;
    }
    for (I j = 0; j < 10; j++) {
      for (I k = 0; k < 2; k++) {
        const I beg = 0;
        const I end = k >> 0 & 1 ? dgts[i] : 9;
        for (I l = beg; l <= end; l++) {
          if (j != l) {
            const I msk = (k >> 0 & 1 ? l == dgts[i] : 0) << 0;
            dp[i + 1][l][msk] += dp[i][j][k];
          }
        }
      }
    }
  }
  Lli res = 1;
  for (I i = 0; i < 10; i++)
    for (I j = 0; j < 2; j++)
      res += dp[len][i][j];
  return res;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  Lli a, b;
  cin >> a >> b;
  printf("%lli\n", slv(b) - slv(a - 1));
  return 0;
}