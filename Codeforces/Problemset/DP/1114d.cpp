#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 5000;

I c_arr[N];
pair<I, I> dp[N][N];

pair<I, I> slv(I l, I r) {
  if (l == r)
    return {0, c_arr[l]};
  if (dp[l][r].first != -1)
    return dp[l][r];
  auto [l_lft, l_rgt] = slv(l + 1, r);
  auto [r_lft, r_rgt] = slv(l, r - 1);
  l_lft += c_arr[l] != c_arr[l + 1];
  l_rgt += c_arr[l] != c_arr[r];
  r_lft += c_arr[r] != c_arr[l];
  r_rgt += c_arr[r] != c_arr[r - 1];
  return dp[l][r] = {min(l_lft, l_rgt), min(r_lft, r_rgt)};
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(pair<I, I>), pair<I, I>(-1, -1));
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> c_arr[i];
  const auto [l_tot, r_tot] = slv(0, n - 1);
  printf("%i\n", min(l_tot, r_tot));
  return 0;
}