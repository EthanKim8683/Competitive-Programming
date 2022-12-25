#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

using I = int;

set<I> x_set;
set<I> y_set;
pair<I, I> cows[100];

I main(void) {
  freopen("balancing.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("balancing.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, b;
  cin >> n >> b;
  for (I i = n; i--;) {
    I x, y;
    cin >> x >> y;
    x_set.insert(x);
    y_set.insert(y);
    cows[i] = {x, y};
  }
  I result = 1e9;
  for (const auto a : x_set) {
    for (const auto b : y_set) {
      I q1 = 0;
      I q2 = 0;
      I q3 = 0;
      I q4 = 0;
      for (I i = n; i--;) {
        const auto [x, y] = cows[i];
        switch ((x < a) << 1 | (y < b)) {
          case 0b00:
            q1++;
            break;
          case 0b01:
            q2++;
            break;
          case 0b10:
            q3++;
            break;
          case 0b11:
            q4++;
            break;
        }
      }
      result = min(result, max(q1, max(q2, max(q3, q4))));
    }
  }
  printf("%i\n", result);
  return 0;
}