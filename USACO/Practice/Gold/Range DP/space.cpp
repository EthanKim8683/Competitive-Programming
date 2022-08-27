#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using S = string;

const I N = 500;
const I MAX = 1e9;

S str;
I dp[N][N];

I slv(I l, I r) {
  if (l > r)
    return 0;
  if (dp[l][r] != -1)
    return dp[l][r];
  I res = slv(l + 1, r) + 1;
  for (I i = l + 1; i <= r; i++)
    if (str[l] == str[i])
      res = min(res, slv(l + 1, i - 1) + slv(i + 1, r));
  return dp[l][r] = res;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(I), -1);
  cin >> str;
  printf("%i\n", slv(0, str.size() - 1));
  return 0;
}