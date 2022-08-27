#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

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
  I c;
  cin >> c;
  while (c--) {
    I x, y, n;
    cin >> x >> y >> n;
    printf("%lli\n", pow(x, y, n));
  }
  return 0;
}