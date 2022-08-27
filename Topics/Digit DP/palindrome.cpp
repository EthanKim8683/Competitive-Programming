#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;
using Lli = long long int;

const I L = 18;

// 1. current index
// 2. start index
// 3. l < upp, l = upp
// 4. r <= upp, r > upp
Lli dp[L + 1][L][2][2];
vector<I> dgts;

Lli slv(Lli upp) {
  fill(&dp[0][0][0][0], &dp[0][0][0][0] + sizeof(dp) / sizeof(Lli), 0);
  dgts.clear();
  I len = 0;
  while (upp) {
    dgts.push_back(upp % 10);
    upp /= 10;
    len++;
  }
  reverse(dgts.begin(), dgts.end());
  for (I i = 0; i < len; i++) {
    dp[i][i][i == 0][0]++;
    for (I j = 0; j <= i; j++) {
      const I k = len - 1 - (i - j);
      if (i <= k) {
        for (I l = 0; l < 2; l++)
          for (I m = 0; m < 2; m++)
            for (I n = i == j; n < (l & 1 ? dgts[i] : 10); n++)
              dp[i + 1][j][l][m] += dp[i][j][l][m];
        dp[i + 1][j][1][dgts[i] > dgts[k]] += dp[i][j][1][0];
        dp[i + 1][j][1][dgts[i] >= dgts[k]] += dp[i][j][1][1];
      } else
        for (I l = 0; l < 2; l++)
          for (I m = 0; m < 2; m++)
            dp[i + 1][j][l][m] += dp[i][j][l][m];
    }
  }
  Lli res = 1;
  for (I i = 0; i < len; i++)
    res += dp[len][i][0][0] + dp[len][i][0][1] + dp[len][i][1][0];
  return res;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  for (I i = 1; i <= t; i++) {
    Lli l, r;
    cin >> l >> r;
    if (l > r)
      swap(l, r);
    Lli l_res = 0;
    Lli r_res = 1;
    if (l != 0)
      l_res = slv(l - 1);
    if (r != 0)
      r_res = slv(r);
    printf("Case %i: %lli\n", i, r_res - l_res);
  }
  return 0;
}