#include <iostream>
#include <cstdio>
#include <tuple>

using namespace std;

using I = int;
using B = bool;

const I MIN = -1e9;
const I MAX = 1e9;

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

I flr_div(I a, I b) {
  return a / b - (a % b != 0 && (a < 0) != (b < 0));
}

I clg_div(I a, I b) {
  return a / b + (a % b != 0 && (a < 0) == (b < 0));
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I a, b, c;
  cin >> a >> b >> c;
  B res = false;
  // a * x + b * y = g
  // a * x * (c / g) + b * y * (c / g) = c
  auto [x, y, g] = gcd(a, b);
  const I q = c / g;
  if (g * q == c) {
    x *= q;
    y *= q;
    // 0 <= x + f * (b / g)
    // 0 <= y - f * (a / g)
    // -x / (b / g) <= f
    // f <= y / (a / g)
    if (clg_div(-x, b / g) <= flr_div(y, a / g))
      res = true;
  }
  if (res)
    printf("Yes\n");
  else
    printf("No\n");
  return 0;
}