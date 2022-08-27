#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 3000;
const Lli MIN = -1e18;

I a_arr[N];
Lli dp[N][N];

Lli slv(I l, I r) {
  if (l > r)
    return 0;
  if (l == r)
    return a_arr[l];
  if (dp[l][r] != MIN)
    return dp[l][r];
  return dp[l][r] = max(a_arr[l] - slv(l + 1, r), a_arr[r] - slv(l, r - 1));
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(Lli), MIN);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  printf("%lli\n", slv(0, n - 1));
  return 0;
}