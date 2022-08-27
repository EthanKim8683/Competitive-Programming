#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MOD = 1000000007;

Lli mod(Lli i) {
  return i % MOD + (i < 0) * MOD;
}

pair<Lli, Lli> fib(I i) {
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

Lli sum(I i) {
  return mod(fib(i + 1).first - 1);
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I n, m;
    cin >> n >> m;
    printf("%lli\n", mod(sum(m + 1) - sum(n)));
  }
  return 0;
}