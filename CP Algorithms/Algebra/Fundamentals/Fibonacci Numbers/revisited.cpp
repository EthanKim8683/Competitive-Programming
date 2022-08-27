#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MOD = 1000000007;

Lli mod(Lli i) {
  return i % MOD + (i < 0) * MOD;
}

pair<Lli, Lli> fib(Lli i) {
  if (i == 0)
    return {0, 1};
  const auto [a0, a1] = fib(i >> 1);
  const Lli b0 = mod(a0 * (2 * a1 - a0));
  const Lli b1 = mod(a0 * a0 + a1 * a1);
  if (i & 1)
    return {b1, mod(b0 + b1)};
  else
    return {b0, b1};
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    Lli n;
    cin >> n;
    if (n == 0)
      printf("0\n");
    else if (n == 1)
      printf("2\n");
    else {
      const auto [f0, f1] = fib(n + 1);
      printf("%lli\n", mod(f0 + f1));
    }
  }
  return 0;
}