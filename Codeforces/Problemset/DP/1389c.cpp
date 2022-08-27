#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

using I = int;
using S = string;

const I N = 2e5;

I dp[10][10];

I main(void) {
#ifdef ETHANKIM8683
  freopen("1389c.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    S s;
    cin >> s;
    for (I i = 0; i < 10; i++)
      fill_n(dp[i], 10, 0);
    for (const auto chr : s) {
      const I dgt = chr - '0';
      for (I i = 0; i < 10; i++) {
        if (i != dgt) {
          if (dp[dgt][i] % 2 == 0)
            dp[dgt][i]++;
          if (dp[i][dgt] % 2 == 1)
            dp[i][dgt]++;
        } else
          dp[dgt][dgt]++;
      }
    }
    I res = 0;
    for (I i = 0; i < 10; i++) {
      for (I j = 0; j < 10; j++) {
        auto len = dp[i][j];
        if (i != j)
          len &= ~1;
        res = max(res, len);
      }
    }
    res = s.length() - res;
    printf("%i\n", res);
  }
  return 0;
}