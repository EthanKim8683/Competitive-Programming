#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 400;
const Lli MAX = 1e18;

I a_arr[N];
Lli dp[N][N];
Lli ps[N + 1];
I n;

Lli rng(I l, I r) {
  return ps[r + 1] - ps[l];
}

Lli slv(I l, I r) {
  if (l >= r)
    return 0;
  if (dp[l][r] != -1)
    return dp[l][r];
  Lli res = MAX;
  for (I i = l; i < r; i++)
    res = min(res, slv(l, i) + slv(i + 1, r));
  return dp[l][r] = res + rng(l, r);
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(Lli), -1);
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  for (I i = 0; i < n; i++)
    ps[i + 1] = ps[i] + a_arr[i];
  printf("%lli\n", slv(0, n - 1));
  return 0;
}