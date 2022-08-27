#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e6;
const Lli MOD = 1e9 + 7;

Lli dp1[N + 1];
Lli dp2[N + 1];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  dp1[3] = 1;
  for (I i = 4; i <= N; i++)
    dp1[i] = (dp1[i - 1] + 2 * dp1[i - 2]) % MOD;
  for (I i = 3; i <= N; i++)
    dp2[i] = (dp2[i - 3] + dp1[i]) % MOD;
  I t;
  cin >> t;
  while (t--) {
    I n;
    cin >> n;
    printf("%lli\n", dp2[n] * 4 % MOD);
  }
  return 0;
}