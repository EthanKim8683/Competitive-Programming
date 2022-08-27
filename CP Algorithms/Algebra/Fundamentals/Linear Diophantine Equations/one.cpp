#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

Lli gcd(Lli a, Lli b) {
  while (b) {
    a %= b;
    swap(a, b);
  }
  return a;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    Lli a, b;
    cin >> a >> b;
    Lli res = -1;
    if (gcd(a, b) == 1)
      res = (a - 1) * (b - 1);
    printf("%lli\n", res);
  }
  return 0;
}