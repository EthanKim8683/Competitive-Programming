#include <iostream>
#include <cstdio>

using namespace std;

using I = int;

const I N = 1e5;

pair<I, I> trees[N];
I dp[N + 1];

I main(void) {
#ifdef ETHANKIM8683
  freopen("545c.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    I x, h;
    cin >> x >> h;
    trees[i] = {x, h};
  }
  for (I i = 0; i < n; i++) {
    const auto [x, h] = trees[i];
    if (i + 1 < n) {
      if (trees[i + 1].first > x + h)
        dp[i + 1] = max(dp[i + 1], dp[i] + 1);
    } else
      dp[n] = max(dp[n], dp[i] + 1);
    if (i - 1 >= 0) {
      if (trees[i - 1].first < x - h)
        dp[i] = max(dp[i], dp[i - 1] + 1);
    } else
      dp[i] = max(dp[i], 1);
    dp[i + 1] = max(dp[i + 1], dp[i]);
  }
  printf("%i\n", dp[n]);
  return 0;
}