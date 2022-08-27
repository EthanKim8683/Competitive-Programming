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
  while (true) {
    I a = 0, b = 0;
    cin >> a >> b;
    if (a == 0 && b == 0)
      break;
    auto [x, y, g] = gcd(a, b);
    printf("%i %i %i\n", x, y, g);
  }
  return 0;
}