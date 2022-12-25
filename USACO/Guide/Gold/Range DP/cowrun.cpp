#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 1000;
const Lli MAX = 1e18;

I p_arr[N];
Lli dp[N + 1][N + 1][2];
vector<I> lows;
vector<I> upps;
I n;

void cmb(Lli& a, Lli b) {
  a = min(a, b);
}

Lli dfs(I l, I r, I sid, I cur) {
  if (l == lows.size() && r == upps.size())
    return 0;
  if (dp[l][r][sid] != MAX)
    return dp[l][r][sid];
  const I cnt = n - l - r;
  if (l < lows.size())
    cmb(dp[l][r][sid], dfs(l + 1, r, 0, lows[l]) + cnt * abs(lows[l] - cur));
  if (r < upps.size())
    cmb(dp[l][r][sid], dfs(l, r + 1, 1, upps[r]) + cnt * abs(upps[r] - cur));
  return dp[l][r][sid];
}

I main(void) {
#ifndef ETHANKIM8683
  freopen("cowrun.in", "r", stdin);
  freopen("cowrun.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp) / sizeof(Lli), MAX);
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> p_arr[i];
  for (I i = 0; i < n; i++) {
    const I p = p_arr[i];
    if (p < 0)
      lows.push_back(p);
    if (p > 0)
      upps.push_back(p);
  }
  sort(lows.begin(), lows.end(), greater<I>());
  sort(upps.begin(), upps.end());
  printf("%lli\n", min(dfs(0, 0, 0, 0), dfs(0, 0, 1, 0)));
  return 0;
}