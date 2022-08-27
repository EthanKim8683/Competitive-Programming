#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;
using S = string;

const I L = 55;

// 1. current index
// 2. x < upp, x = upp
Lli dp[L + 1][2];
B incs[10];
vector<I> dgts;
I b;

Lli slv(Lli upp) {
  fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(Lli), 0);
  dgts.clear();
  I len = 0;
  while (upp) {
    dgts.push_back(upp % b);
    upp /= b;
    len++;
  }
  reverse(dgts.begin(), dgts.end());
  for (I i = 0; i < len; i++) {
    const I beg = 1;
    const I end = i == 0 ? dgts[0] : b - 1;
    for (I j = beg; j <= end; j++) {
      if (incs[j]) {
        const I msk = (i == 0 ? j == dgts[0] : 0) << 0;
        dp[i + 1][msk]++;
      }
    }
    for (I j = 0; j < 2; j++) {
      const I beg = 0;
      const I end = j >> 0 & 1 ? dgts[i] : b - 1;
      for (I k = beg; k <= end; k++) {
        if (incs[k]) {
          const I msk = (j >> 0 & 1 ? k == dgts[i] : 0) << 0;
          dp[i + 1][msk] += dp[i][j];
        }
      }
    }
  }
  Lli res = 0;
  for (I i = 0; i < 2; i++)
    res += dp[len][i];
  return res;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  while (true) {
    Lli d, h;
    S l;
    cin >> d >> h >> b >> l;
    if (l == "*")
      break;
    for (I i = 0; i < b; i++)
      incs[i] = l[i] == 'S';
    printf("%lli\n", slv(h) - slv(d - 1));
  }
  return 0;
}