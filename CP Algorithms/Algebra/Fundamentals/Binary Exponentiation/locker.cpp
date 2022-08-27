#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MOD = 1e9 + 7;

Lli pow(Lli bse, Lli pow, Lli mod) {
  Lli res = 1;
  while (pow) {
    if (pow & 1)
      res = res * bse % mod;
    pow >>= 1;
    bse = bse * bse % mod;
  }
  return res;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    Lli n;
    cin >> n;
    Lli mul = 1;
    if (n % 3 == 1) {
      if (n > 3) {
        mul = 4;
        n -= mul;
      }
    } else if (n % 3 == 2) {
      mul = 2;
      n -= mul;
    }
    printf("%lli\n", pow(3, n / 3 % (MOD - 1), MOD) * mul % MOD);
  }
  return 0;
}