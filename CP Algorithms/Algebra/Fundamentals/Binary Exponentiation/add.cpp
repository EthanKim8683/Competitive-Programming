#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MOD = 1e7 + 7;

Lli pow(Lli bse, Lli pow) {
  bse %= MOD;
  Lli res = 1;
  while (pow) {
    if (pow & 1)
      res = res * bse % MOD;
    pow >>= 1;
    bse = bse * bse % MOD;
  }
  return res;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  while (true) {
    Lli n, k;
    cin >> n >> k;
    if (n == 0 && k == 0)
      break;
    const Lli a_p = pow(n, k);
    const Lli a_s = pow(n, n);
    const Lli b_p = pow(n - 1, k);
    const Lli b_s = pow(n - 1, n - 1);
    printf("%lli\n", (a_p + a_s + 2 * (b_p + b_s)) % MOD);
  }
  return 0;
}