#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using C = char;

U ps[1001][1001];

int main(void) {
#if defined(ETHANKIM8683)
  freopen("forest.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, q;
  cin >> n >> q;
  for (U y = 1; y <= n; y++) {
    for (U x = 1; x <= n; x++) {
      C c;
      cin >> c;
      ps[y][x] = (c == '*') + ps[y - 1][x] + ps[y][x - 1] - ps[y - 1][x - 1];
    }
  }
  while (q--) {
    U y1, x1, y2, x2;
    cin >> y1 >> x1 >> y2 >> x2;
    x1--;
    y1--;
    printf("%u\n", ps[y2][x2] - ps[y2][x1] - ps[y1][x2] + ps[y1][x1]);
  }
  return 0;
}