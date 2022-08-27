#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using B = bool;
using Lli = long long int;

const I N = 21;
const Lli MOD = 1e9 + 7;

B mat[N][N];
Lli dp[1 << N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    for (I j = 0; j < n; j++)
      cin >> mat[i][j];
  dp[0] = 1;
  for (I j = 0; j < (1 << n); j++)
    for (I k = 0; k < n; k++)
      if (~j >> k & 1)
        if (mat[__builtin_popcount(j)][k])
          (dp[j | 1 << k] += dp[j]) %= MOD;
  printf("%lli\n", dp[(1 << n) - 1]);
  return 0;
}