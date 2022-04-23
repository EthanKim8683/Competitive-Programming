#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using U = unsigned;
using I = int;
using B = bool;

U x_min[2001];
U x_max[2001];
U y_min[2001];
U y_max[2001];
pair<U, U> points[200];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("33.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  fill_n(x_min, 2001, 2001);
  fill_n(y_min, 2001, 2001);
  for (U i = n; i--;) {
    auto& [x, y] = points[i];
    cin >> x >> y;
    x += 1000;
    y += 1000;
    x_min[y] = min(x_min[y], x);
    x_max[y] = max(x_max[y], x);
    y_min[x] = min(y_min[x], y);
    y_max[x] = max(y_max[x], y);
  }
  U result = 0;
  for (U i = n; i--;) {
    const auto [x, y] = points[i];
    result += x > x_min[y] && x < x_max[y] &&
              y > y_min[x] && y < y_max[x];
  }
  printf("%u\n", result);
  return 0;
}