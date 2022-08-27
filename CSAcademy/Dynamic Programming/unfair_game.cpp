#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MIN = -1e18;
const I N = 1e5;

I a_arr[N];
Lli dp[2][N + 1];

I main(void) {
#ifdef ETHANKIM8683
  freopen("unfair_game.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < 2; i++)
    fill_n(dp[i], n + 1, MIN);
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  // optimal moves achieved through sorting
  sort(a_arr, a_arr + n, greater<I>());
  dp[0][1] = a_arr[0];
  for (I i = 1; i < n; i++) {
    const auto a = a_arr[i];
    // alex to alex
    dp[0][i + 1] = max(dp[0][i + 1], dp[0][i] + a);
    // ben to alex
    dp[0][i + 1] = max(dp[0][i + 1], dp[1][i] + a);
    // alex to ben
    dp[1][i + 1] = max(dp[1][i + 1], dp[0][i]);
  }
  printf("%lli\n", max(dp[0][n], dp[1][n]));
  return 0;
}