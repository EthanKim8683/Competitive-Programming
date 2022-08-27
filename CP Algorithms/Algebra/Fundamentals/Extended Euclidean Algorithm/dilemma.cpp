#include <iostream>
#include <cstdio>
#include <tuple>

using namespace std;

using I = int;

tuple<I, I, I> gcd(I a, I b) {
  I x = 1, y = 0, z = 0, w = 1;
  while (b) {
    const I q = a / b;
    tie(x, z) = make_pair(z, x - q * z);
    tie(y, w) = make_pair(w, y - q * w);
    tie(a, b) = make_pair(b, a - q * b);
  }
  return {x, y, a};
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  for (I i = 1; i <= t; i++) {
    I a, b, c, p;
    cin >> a >> b >> c >> p;
    // (a * x + b * y) * z + c * w = gcd(a, b, c)
    // a * x * z + b * y * z + c * w = gcd(a, b, c)
    const auto [x, y, g] = gcd(a, b);
    const auto [z, w, f] = gcd(g, c);
    I res = 0;
    const I q = p / f;
    if (p % f == 0) {
      
    } else
      printf("Case %i: 0\n", i);
  }
  return 0;
}