#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using B = bool;

const I X = 1e7;

I prms[X * 2 + 1];
I c, d;

I chk(I i) {
  // assuming a, b are coprime,
  // x % i = 0
  // c * a * b - d = i
  // a * b = (i + d) / c
  const I ab = (i + d) / c;
  if (c * ab - d != i)
    return 0;
  // f = # of prime factors
  // c = # of coprime factors
  // c = 2 ^ f
  return 1 << prms[ab];
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("pairs.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  for (I i = 2; i <= X * 2; i++)
    if (prms[i] == 0)
      for (I j = i; j <= X * 2; j += i)
        prms[j]++;
  while (t--) {
    I x;
    cin >> c >> d >> x;
    I res = 0;
    for (I i = 1; i * i <= x; i++) {
      if (x % i == 0) {
        res += chk(i);
        if (i != x / i)
          res += chk(x / i);
      }
    }
    printf("%i\n", res);
  }
  return 0;
}