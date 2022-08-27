#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;
using S = string;

Lli pow(Lli bse, Lli exp) {
  Lli res = 1;
  while (exp) {
    if (exp & 1)
      res *= bse;
    bse *= bse;
    exp >>= 1;
  }
  return res;
}

Lli rng(I val) {
  if (val < 1)
    return 0;
  return val * 45 * pow(10, val - 1);
}

pair<Lli, Lli> slv(S upp) {
  Lli res = 0;
  Lli sum = 0;
  const I len = upp.size();
  for (I i = 0; i < len; i++) {
    const I dgt = upp[i] - '0';
    const I rem = len - i - 1;
    for (I j = 0; j < dgt; j++)
      res += (sum + j) * pow(10, rem) + rng(rem);
    sum += dgt;
  }
  return {res, sum};
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  while (true) {
    S a, b;
    cin >> a >> b;
    if (a == "-1" && b == "-1")
      break;
    const auto [b_les, b_equ] = slv(b);
    const auto [a_les, a_equ] = slv(a);
    printf("%lli\n", b_les + b_equ - a_les);
  }
  return 0;
}