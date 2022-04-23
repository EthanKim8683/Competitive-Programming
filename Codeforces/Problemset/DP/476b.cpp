#include <iostream>
#include <cstdio>

#define N 10
#define M ((N) * 2 + 1)

using namespace std;

using I = int;
using Lf = double;
using S = string;

Lf dp[N + 1][M];

I main(void) {
#ifdef ETHANKIM8683
  freopen("476b.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  S s1, s2;
  cin >> s1;
  cin >> s2;
  I original = 10;
  for (const auto c : s1) {
    switch (c) {
      case '+':
        original++;
        break;
      case '-':
        original--;
        break;
    }
  }
  dp[0][10] = 1;
  I t = 0;
  for (const auto c : s2) {
    switch (c) {
      case '?':
        for (I i = 0; i < M; i++) {
          if (i + 1 < M)
            dp[t + 1][i + 1] += dp[t][i] * 0.5;
          if (i - 1 >= 0)
            dp[t + 1][i - 1] += dp[t][i] * 0.5;
        }
        break;
      case '+':
        for (I i = 0; i < M - 1; i++)
          dp[t + 1][i + 1] = dp[t][i];
        break;
      case '-':
        for (I i = 1; i < M; i++)
          dp[t + 1][i - 1] = dp[t][i];
        break;
    }
    t++;
  }
  printf("%.10lf", dp[t][original]);
  return 0;
}