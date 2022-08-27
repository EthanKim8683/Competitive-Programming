#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 5000;
const Lli MIN = -1e18;

I x_arr[N];
Lli ps[N + 1];
Lli dp[N][N];

Lli rng(I l, I r) {
  return ps[r + 1] - ps[l];
}

Lli slv(I l, I r) {
  if (l > r)
    return 0;
  if (dp[l][r] != MIN)
    return dp[l][r];
  const Lli l_scr = x_arr[l] + rng(l + 1, r) - slv(l + 1, r);
  const Lli r_scr = x_arr[r] + rng(l, r - 1) - slv(l, r - 1);
  return dp[l][r] = max(l_scr, r_scr);
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(Lli), MIN);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> x_arr[i];
  for (I i = 0; i < n; i++)
    ps[i + 1] = ps[i] + x_arr[i];
  printf("%lli\n", slv(0, n - 1));
  return 0;
}