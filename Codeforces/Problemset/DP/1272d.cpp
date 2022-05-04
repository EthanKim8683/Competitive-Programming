#include <iostream>
#include <cstdio>

using namespace std;

using I = int;

const I N = 2e5;

I a_arr[N];
pair<I, I> dp[N + 1][2];

I main(void) {
#ifdef ETHANKIM8683
  freopen("1272d.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  I res = 0;
  for (I i = 1; i <= n; i++) {
    const auto a = a_arr[i - 1];
    // don't skip
    const auto [a_len, a_lst] = dp[i - 1][0];
    if (a > a_lst)
      dp[i][0] = {a_len + 1, a};
    else
      dp[i][0] = {1, a};
    const auto [c_len, c_lst] = dp[i - 1][1];
    if (a > c_lst)
      dp[i][1] = {c_len + 1, a};
    else
      dp[i][1] = {1, a};
    // do skip
    if (i - 2 >= 0) {
      const auto [b_len, b_lst] = dp[i - 2][0];
      if (a > b_lst)
        dp[i][1] = {max(dp[i][1].first, b_len + 1), a};
      else
        dp[i][1] = {max(dp[i][1].first, 1), a};
    }
    res = max(res, dp[i][0].first);
    res = max(res, dp[i][1].first);
  }
  printf("%i\n", res);
  return 0;
}