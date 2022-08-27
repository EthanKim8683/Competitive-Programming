#include <iostream>
#include <cstdio>
#include <tuple>

using namespace std;

using I = int;
using Lli = long long int;

tuple<Lli, Lli, Lli> gcd(Lli a, Lli b) {
  Lli x = 1, y = 0, z = 0, w = 1;
  while (b) {
    const Lli q = a / b;
    tie(x, z) = make_pair(z, x - q * z);
    tie(y, w) = make_pair(w, y - q * w);
    tie(a, b) = make_pair(b, a - q * b);
  }
  return {x, y, a};
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  while (true) {
    Lli a1, m1, m2, a2;
    cin >> a1 >> m1 >> m2 >> a2;
    if (a1 == 0 && m1 == 0 && m2 == 0 && a2 == 0)
      break;
    a2 += m2;
    const auto [p, q, g] = gcd(m1, m2);
    if (a1 % g == a2 % g) {
      const Lli lcm = m1 / g * m2;
      Lli res = (a1 * m2 / g * q + a2 * m1 / g * p) % lcm;
      while (res < a1 || res < a2)
        res += lcm;
      printf("%lli\n", res);
    } else
      printf("Impossible\n");
  }
  return 0;
}