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

Lli flr_div(Lli a, Lli b) {
  return a / b - (a % b != 0 && (a < 0) != (b < 0));
}

Lli clg_div(Lli a, Lli b) {
  return a / b + (a % b != 0 && (a < 0) == (b < 0));
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  for (I i = 1; i <= t; i++) {
    Lli a, b, c, x1, x2, y1, y2;
    cin >> a >> b >> c >> x1 >> x2 >> y1 >> y2;
    c *= -1;
    Lli res = 0;
    if (a == 0 && b == 0) {
      // 0 = c
      if (c == 0)
        res = (x2 - x1 + 1) * (y2 - y1 + 1);
    } else if (a == 0) {
      // b * y = c
      if (c % b == 0) {
        // y1 <= y <= y2
        // y1 <= c / b <= y2
        c /= b;
        if (c >= y1 && c <= y2)
          res = x2 - x1 + 1;
      }
    } else if (b == 0) {
      // a * x = c
      if (c % a == 0) {
        // x1 <= x <= x2
        // x1 <= c / a <= x2
        c /= a;
        if (c >= x1 && c <= x2)
          res = y2 - y1 + 1;
      }
    } else {
      // a * x + b * y = g
      // a * x * (c / g) + b * x * (c / g) = c
      auto [x, y, g] = gcd(a, b);
      const Lli q = c / g;
      if (g * q == c) {
        x *= q;
        y *= q;
        // x1 <= x + f * (b / g) <= x2
        // y1 <= y - f * (a / g) <= y2
        // (x1 - x) / (b / g) <= f <= (x2 - x) / (b / g)
        // (y - y2) / (a / g) <= f <= (y - y1) / (a / g)
        a /= g;
        b /= g;
        if (b < 0)
          swap(x1, x2);
        if (a < 0)
          swap(y1, y2);
        const Lli low = max(clg_div(x1 - x, b), clg_div(y - y2, a));
        const Lli upp = min(flr_div(x2 - x, b), flr_div(y - y1, a));
        res = upp - low + 1;
      }
    }
    printf("Case %i: %lli\n", i, max(res, (Lli) 0));
  }
  return 0;
}