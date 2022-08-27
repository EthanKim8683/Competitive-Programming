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
  Lli n;
  cin >> n;
  const Lli odd = n / 2;
  const Lli evn = n - odd;
  printf("%lli\n", pow(5, evn % (MOD - 1), MOD) * pow(4, odd % (MOD - 1), MOD) % MOD);
  return 0;
}