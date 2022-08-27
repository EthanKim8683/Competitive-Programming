#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e5;
const Lli MOD = 1e9 + 7;

Lli cnts[3];
Lli dp[N + 1][3];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, l, r;
  cin >> n >> l >> r;
  l--;
  fill_n(cnts, 3, r / 3 - l / 3);
  for (I i = 0; i <= r % 3; i++)
    cnts[i]++;
  for (I i = 0; i <= l % 3; i++)
    cnts[i]--;
  dp[0][0] = 1;
  for (I i = 0; i < n; i++)
    for (I j = 0; j < 3; j++)
      for (I k = 0; k < 3; k++)
        (dp[i + 1][(j + k) % 3] += dp[i][j] * cnts[k]) %= MOD;
  printf("%lli\n", dp[n][0]);
  return 0;
}