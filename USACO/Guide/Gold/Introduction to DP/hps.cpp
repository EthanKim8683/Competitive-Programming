#include <iostream>
#include <cstdio>

#define N 100000

using namespace std;

using I = int;
using C = char;

I gestures[N];
I dp[N][21][3];
C line[2];

I main(void) {
  freopen("hps.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("hps.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, k;
  cin >> n >> k;
  const I x = n - 1;
  for (I i = 0; i < n; i++) {
    cin >> line;
    switch (line[0]) {
      case 'H':
        gestures[i] = 0;
        break;
      case 'P':
        gestures[i] = 1;
        break;
      case 'S':
        gestures[i] = 2;
        break;
    }
  }
  const auto john = gestures[0];
  dp[0][0][0] = john == 0;
  dp[0][0][1] = john == 1;
  dp[0][0][2] = john == 2;
  for (I i = 0; i < n - 1; i++) {
    const I j = i + 1;
    const auto john = gestures[j];
    for (I moves = 0; moves <= k; moves++) {
      for (I bessie = 3; bessie--;) {
        const auto wins = dp[i][moves][bessie];
        const I h_moves = moves + (bessie != 0);
        const I p_moves = moves + (bessie != 1);
        const I s_moves = moves + (bessie != 2);
        if (h_moves <= k) {
          auto& h = dp[j][h_moves][0];
          h = max(h, wins + (john == 0));
        }
        if (p_moves <= k) {
          auto& p = dp[j][p_moves][1];
          p = max(p, wins + (john == 1));
        }
        if (s_moves <= k) {
          auto& s = dp[j][s_moves][2];
          s = max(s, wins + (john == 2));
        }
      }
    }
  }
  I result = 0;
  for (I moves = 0; moves <= k; moves++)
    for (I bessie = 3; bessie--;)
      result = max(result, dp[x][moves][bessie]);
  printf("%i\n", result);
  return 0;
}