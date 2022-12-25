#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MOD = 2 * (1e9 + 7);
const I N = 500;
const I M = N * (N + 1) / 2;

Lli dp[M];

I main(void) {
#ifdef ETHANKIM8683
  freopen("sets2.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  const I m = n * (n + 1) / 2;
  if (m % 2 == 0) {
    dp[0] = 1;
    for (I i = 1; i <= n; i++)
      for (I j = M; j--;)
        if (j + i <= M)
          dp[j + i] = (dp[j + i] + dp[j]) % MOD;
    printf("%lli\n", dp[m / 2] / 2);
  } else
    printf("0\n");
  return 0;
}