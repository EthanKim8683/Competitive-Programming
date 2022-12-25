#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const I N = 21;
const Lli MOD = 1e9 + 7;

I coms[N];
Lli dp[1 << N];

Lli mod(Lli i) {
  return i >= MOD ? i % MOD : i;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("matching.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    for (I j = 0; j < n; j++) {
      I c;
      cin >> c;
      coms[i] |= c << j;
    }
  }
  dp[0] = 1;
  for (I i = 0; i < n; i++)
    for (I j = (1 << n) - 1; j >= 0; j--)
      if (__builtin_popcount(j) == i)
        for (I k = 0; k < n; k++)
          if (~j & coms[i] & (1 << k))
            dp[j | (1 << k)] = mod(dp[j | (1 << k)] + dp[j]);
  printf("%lli\n", dp[(1 << n) - 1]);
  return 0;
}