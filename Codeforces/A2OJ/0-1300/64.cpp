#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using I = int;
using C = char;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("64.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U t;
  I sx, sy, ex, ey;
  cin >> t >> sx >> sy >> ex >> ey;
  I dx = ex - sx;
  I dy = ey - sy;
  U result = 0;
  for (; result < t; result++) {
    if (!dx && !dy)
      break;
    C c;
    cin >> c;
    switch (c) {
      case 'N':
        if (dy > 0)
          dy--;
        break;
      case 'E':
        if (dx > 0)
          dx--;
        break;
      case 'S':
        if (dy < 0)
          dy++;
        break;
      case 'W':
        if (dx < 0)
          dx++;
        break;
    }
  }
  if (dx || dy)
    printf("-1");
  else
    printf("%u", result);
  return 0;
}