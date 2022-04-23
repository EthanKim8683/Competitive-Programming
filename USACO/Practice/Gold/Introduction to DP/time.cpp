#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

#define T 1000
#define N 1000

using namespace std;

using I = int;

vector<I> adjs[N];
I cities[N];
I dp[T][N];

I main(void) {
  freopen("time.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("time.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m, c;
  cin >> n >> m >> c;
  for (I i = 0; i < n; i++)
    cin >> cities[i];
  while (m--) {
    I a, b;
    cin >> a >> b;
    adjs[a - 1].push_back(b - 1);
  }
  for (I t = 0; t < T; t++)
    fill_n(dp[t], n, -1);
  dp[0][0] = 0;
  for (I t = 0; t < T - 1; t++) {
    for (I a = 0; a < n; a++) {
      if (dp[t][a] != -1) {
        const I moonies = dp[t][a] + cities[a];
        for (const auto b : adjs[a])
          dp[t + 1][b] = max(dp[t + 1][b], moonies);
      }
    }
  }
  I result = 0;
  for (I t = 0; t < T; t++)
    result = max(result, dp[t][0] - c * t * t);
  printf("%i\n", result);
  return 0;
}