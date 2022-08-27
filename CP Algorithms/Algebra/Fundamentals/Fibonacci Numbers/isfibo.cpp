#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Li = long int;
using Lli = long long int;
using S = string;

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

S isFibo(Lli n) {
  I l = 0;
  I r = 50;
  while (l <= r) {
    const I m = l + (r - l) / 2;
    const Lli f = fib(m).first;
    if (f == n)
      return "IsFibo";
    else if (f < n)
      l = m + 1;
    else if (f > n)
      r = m - 1;
  }
  return "IsNotFibo";
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    Lli n;
    cin >> n;
    if (isFibo(n) == "IsFibo")
      printf("%lli\n", n);
  }
  return 0;
}