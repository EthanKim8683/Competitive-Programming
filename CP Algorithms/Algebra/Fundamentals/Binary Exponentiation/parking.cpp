#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

Lli pow(Lli bse, Lli pow) {
  Lli res = 1;
  while (pow) {
    if (pow & 1)
      res *= bse;
    pow >>= 1;
    bse *= bse;
  }
  return res;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  const I m = 2 * n - 2;
  Lli res = 0;
  // left
  if (m - n - 1 >= 0)
    res += pow(4, m - n - 1) * 3;
  // middle
  if (m - n - 2 >= 0)
    res += pow(4, m - n - 2) * 3 * 3 * (m - n - 1);
  // right
  if (m - n - 1 >= 0)
    res += pow(4, m - n - 1) * 3;
  printf("%lli\n", res * 4);
  return 0;
}