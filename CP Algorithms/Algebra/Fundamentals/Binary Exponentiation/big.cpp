#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;
using C = char;

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
  while (true) {
    I b = 0, p = 0, m = 0;
    cin >> b >> p >> m;
    if (b == 0 && p == 0 && m == 0)
      break;
    printf("%lli\n", pow(b, p, m));
  }
  return 0;
}