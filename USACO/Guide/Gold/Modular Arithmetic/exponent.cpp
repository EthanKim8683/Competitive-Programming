#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MOD = 1e9 + 7;

Lli pow(Lli a, Lli b, Lli mod) {
  Lli res = 1;
  while (b) {
    if (b & 1)
      res = res * a % mod;
    b >>= 1;
    a = a * a % mod;
  }
  return res;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("exponent.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    Lli a, b;
    cin >> a >> b;
    printf("%lli\n", pow(a, b, MOD));
  }
  return 0;
}