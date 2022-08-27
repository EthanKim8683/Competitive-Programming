#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MOD = 1e9 + 7;

Lli pow(Lli bse, I exp) {
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
  return pow(bse, MOD - 2) % MOD;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("apples.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  Lli fac = 1;
  for (I i = 1; i < n; i++)
    fac = fac * i % MOD;
  Lli res = inv(fac);
  for (I i = 1; i < n; i++)
    res = res * (m + i) % MOD;
  printf("%lli\n", res);
  return 0;
}