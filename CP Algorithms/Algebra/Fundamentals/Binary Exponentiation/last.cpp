#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

Lli pow(Lli bse, I pow, Lli mod) {
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
    I a, b;
    cin >> a >> b;
    printf("%lli\n", pow(a, b, 10));
  }
  return 0;
}