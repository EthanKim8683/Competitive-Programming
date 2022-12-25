#include <iostream>
#include <cstdio>
#include <stack>

using namespace std;

using I = int;
using Lf = long double;

stack<pair<Lf, Lf>> bals;

Lf slv(Lf d, Lf r) {
  return d * d / (r * 4);
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("balloons.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    Lf x, r;
    cin >> x >> r;
    while (!bals.empty()) {
      const auto [bal_x, bal_r] = bals.top();
      r = min(r, slv(bal_x - x, bal_r));
      if (r < bal_r)
        break;
      bals.pop();
    }
    printf("%.3Lf\n", r);
    if (r > 0)
      bals.push({x, r});
  }
  return 0;
}