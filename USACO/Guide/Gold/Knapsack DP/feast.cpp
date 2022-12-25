#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using B = bool;

const I T = 5000000;

B dp[2][T + 1];

I main(void) {
  freopen("feast.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("feast.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I t, a, b;
  cin >> t >> a >> b;
  dp[0][0] = true;
  for (I i = 0; i < t; i++) {
    if (dp[0][i]) {
      if (i + a <= t)
        dp[0][i + a] = true;
      if (i + b <= t)
        dp[0][i + b] = true;
      dp[1][i / 2] = true;
    }
  }
  for (I i = 0; i < t; i++) {
    if (dp[1][i]) {
      if (i + a <= t)
        dp[1][i + a] = true;
      if (i + b <= t)
        dp[1][i + b] = true;
    }
  }
  I res = t;
  while (!dp[0][res] && !dp[1][res])
    res--;
  printf("%i\n", res);
  return 0;
}