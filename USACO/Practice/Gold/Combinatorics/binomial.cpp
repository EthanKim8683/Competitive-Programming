#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 1e5;
const I A = 1e6;
Lli MOD = 1e9 + 7;

Lli facs[A + 1];

Lli pow(Lli bse, I exp) {
  Lli res = 1;
  while (exp) {
    if (exp & 1)
      res = res * bse % MOD;
    bse = bse * bse % MOD;
    exp >>= 1;
  }
  return res;
}

Lli inv(Lli bse) {
  return pow(bse, MOD - 2);
}

Lli bin(Lli n, Lli k) {
  Lli res = facs[n];
  res = res * inv(facs[k]) % MOD;
  res = res * inv(facs[n - k]) % MOD;
  return res;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("binomial.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  facs[0] = 1;
  for (I i = 1; i <= A; i++)
    facs[i] = facs[i - 1] * i % MOD;
  while (n--) {
    I a, b;
    cin >> a >> b;
    printf("%lli\n", bin(a, b));
  }
  return 0;
}