#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;
using Lli = long long int;
using S = string;

const I L = 19;
const I MIN = -1e9;

// 1. current index
// 2. low < x < upp, low = x < upp, low < x = upp, low = x = upp
pair<S, Lli> dp[L + 1][4];
vector<I> low_dgts;
vector<I> upp_dgts;

S slv(Lli low, Lli upp) {
  fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(pair<S, Lli>), pair<S, Lli>{"", MIN});
  low_dgts.clear();
  upp_dgts.clear();
  I len = 0;
  while (low || upp) {
    low_dgts.push_back(low % 10);
    upp_dgts.push_back(upp % 10);
    low /= 10;
    upp /= 10;
    len++;
  }
  reverse(low_dgts.begin(), low_dgts.end());
  reverse(upp_dgts.begin(), upp_dgts.end());
  if (low_dgts[0] == 0)
    dp[1][0] = {"", 1};
  dp[0][3] = {"", 1};
  for (I i = 0; i < len; i++) {
    for (I j = 0; j < 4; j++) {
      if (dp[i][j].second != MIN) {
        const I beg = j >> 1 & 1 ? low_dgts[i] : 0;
        const I end = j >> 0 & 1 ? upp_dgts[i] : 9;
        for (I k = beg; k <= end; k++) {
          const I msk = (j >> 1 & 1 ? k == low_dgts[i] : 0) << 1 |
                        (j >> 0 & 1 ? k == upp_dgts[i] : 0) << 0;
          if (dp[i][j].second * k > dp[i + 1][msk].second)
            dp[i + 1][msk] = {dp[i][j].first + to_string(k), dp[i][j].second * k};
        }
      }
    }
  }
  pair<S, Lli> res = {"", MIN};
  for (I i = 0; i < 4; i++)
    if (dp[len][i].second > res.second)
    res = dp[len][i];
  return res.first;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  Lli a, b;
  cin >> a >> b;
  printf("%s\n", slv(a, b).c_str());
  return 0;
}