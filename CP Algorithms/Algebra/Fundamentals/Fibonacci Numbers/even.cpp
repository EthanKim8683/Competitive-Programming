#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

pair<Lli, Lli> fib(I i) {
  if (i == 0)
    return {0, 1};
  const auto [a0, a1] = fib(i >> 1);
  const Lli b0 = a0 * (2 * a1 - a0);
  const Lli b1 = a0 * a0 + a1 * a1;
  if (i & 1)
    return {b1, b0 + b1};
  else
    return {b0, b1};
}

Lli val(I i) {
  return fib(i * 3).first;
}

Lli sum(I i) {
  return (fib(i * 3 + 2).first - 1) / 2;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    Lli n;
    cin >> n;
    I l = 0;
    I r = 30;
    while (l < r) {
      const I m = l + (r - l + 1) / 2;
      if (val(m) > n)
        r = m - 1;
      else
        l = m;
    }
    printf("%lli\n", sum(l));
  }
  return 0;
}