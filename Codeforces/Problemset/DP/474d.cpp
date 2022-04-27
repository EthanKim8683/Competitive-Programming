#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MOD = 1e9 + 7;
const I N = 1e5;

Lli dp[N];
Lli ps[N + 1];

Lli mod(Lli x) {
  return x % MOD + (x < 0) * MOD;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("474d.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I t, k;
  cin >> t >> k;
  dp[0] = 1;
  dp[k - 1]++;
  Lli sum = 0;
  for (I i = 0; i < N; i++) {
    if (i + 1 < N)
      dp[i + 1] = (dp[i + 1] + dp[i]) % MOD;
    if (i + k < N)
      dp[i + k] = (dp[i + k] + dp[i]) % MOD;
    sum = (sum + dp[i]) % MOD;
    ps[i + 1] = sum;
  }
  while (t--) {
    I a, b;
    cin >> a >> b;
    printf("%lli\n", mod(ps[b] - ps[a - 1]));
  }
  return 0;
}