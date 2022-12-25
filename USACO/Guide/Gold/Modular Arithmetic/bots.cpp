#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MOD = 1e9 + 7;

Lli pow(Lli bse, Lli exp) {
  Lli res = 1;
  while (exp) {
    if (exp & 1)
      res = res * bse % MOD;
    exp >>= 1;
    bse = bse * bse % MOD;
  }
  return res;
}

Lli inv(Lli bse) {
  return pow(bse, MOD - 2);
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("bots.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  Lli res = pow(2, n + 1) - 1;
  Lli rte = pow(2, n);
  Lli num = 1;
  Lli den = 1;
  for (I i = 1; i <= n; i++) {
    rte = 2 * (rte - num * den % MOD) % MOD;
    num = num * (i + n) % MOD;
    den = den * inv(i) % MOD;
    res = (res + rte) % MOD;
  }
  printf("%lli\n", res + (res < 0) * MOD);
  return 0;
}