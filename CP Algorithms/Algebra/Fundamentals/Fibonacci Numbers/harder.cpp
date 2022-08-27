#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using S = string;
using Lli = long long int;

const I N = 100000;
const Lli MOD = 1e9 + 7;
const Lli PIS = 2e9 + 16;

Lli mod(Lli i, Lli mod) {
  return i % mod + (i < 0) * mod;
}

pair<Lli, Lli> fib(Lli i) {
  if (i == 0)
    return {0, 1};
  const auto [a0, a1] = fib(i >> 1);
  const Lli b0 = mod(a0 * (2 * a1 - a0), MOD);
  const Lli b1 = mod(a0 * a0 + a1 * a1, MOD);
  if (i & 1)
    return {b1, mod(b0 + b1, MOD)};
  else
    return {b0, b1};
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  S n;
  cin >> n;
  Lli res = 0;
  for (const auto dgt : n)
    res = mod(res * 10 + dgt - '0', PIS);
  printf("%lli\n", fib(res).first);
  return 0;
}