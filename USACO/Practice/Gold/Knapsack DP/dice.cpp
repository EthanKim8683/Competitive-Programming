#include <iostream>
#include <cstdio>

using namespace std;

using I = int;

const I MOD = 1e9 + 7;
const I N = 1e6;

I dp[N + 1];

I main(void) {
#ifdef ETHANKIM8683
  freopen("dice.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  dp[0] = 1;
  for (I i = 0; i < n; i++)
    for (I j = 1; j <= 6; j++)
      if (i + j <= n)
        dp[i + j] = (dp[i + j] + dp[i]) % MOD;
  printf("%i\n", dp[n]);
  return 0;
}