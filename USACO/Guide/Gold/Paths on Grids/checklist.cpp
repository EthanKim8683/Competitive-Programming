#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I H = 1000;
const I G = 1000;
const Lli MAX = 1e18;

Lli dp[H + 1][G + 1][2];
pair<I, I> cows[H][2];

Lli sqr(Lli i) {
  return i * i;
}

Lli cst(pair<I, I>& h, pair<I, I>& g) {
  return sqr(h.first - g.first) + sqr(h.second - g.second);
}

I main(void) {
  freopen("checklist.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("checklist.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I h, g;
  cin >> h >> g;
  for (I i = 0; i < h; i++) {
    I x, y;
    cin >> x >> y;
    cows[i][0] = {x, y};
  }
  for (I i = 0; i < g; i++) {
    I x, y;
    cin >> x >> y;
    cows[i][1] = {x, y};
  }
  for (I i = 0; i <= h; i++) {
    for (I j = 0; j <= g; j++) {
      dp[i][j][0] = MAX;
      dp[i][j][1] = MAX;
    }
  }
  dp[1][0][0] = 0;
  for (I i = 0; i <= h; i++) {
    for (I j = 0; j <= g; j++) {
      if (dp[i][j][0] != MAX) {
        if (i + 1 <= h)
          dp[i + 1][j][0] = min(dp[i + 1][j][0], dp[i][j][0] + cst(cows[i - 1][0], cows[i][0]));
        if (j + 1 <= g)
          dp[i][j + 1][1] = min(dp[i][j + 1][1], dp[i][j][0] + cst(cows[i - 1][0], cows[j][1]));
      }
      if (dp[i][j][1] != MAX) {
        if (i + 1 <= h)
          dp[i + 1][j][0] = min(dp[i + 1][j][0], dp[i][j][1] + cst(cows[j - 1][1], cows[i][0]));
        if (j + 1 <= g)
          dp[i][j + 1][1] = min(dp[i][j + 1][1], dp[i][j][1] + cst(cows[j - 1][1], cows[j][1]));
      }
    }
  }
  printf("%lli\n", dp[h][g][0]);
  return 0;
}