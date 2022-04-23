#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using B = bool;

B grid[3][3] = {
  {1, 1, 1},
  {1, 1, 1},
  {1, 1, 1}
};

int main(void) {
#if defined(ETHANKIM8683)
  freopen("6.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  for (U r = 3; r--;) {
    for (U c = 3; c--;) {
      U x;
      cin >> x;
      if (x & 1) {
        if (r > 0)
          grid[r - 1][c] ^= 1;
        if (r < 2)
          grid[r + 1][c] ^= 1;
        if (c > 0)
          grid[r][c - 1] ^= 1;
        if (c < 2)
          grid[r][c + 1] ^= 1;
        grid[r][c] ^= 1;
      }
    }
  }
  for (U r = 3; r--;) {
    for (U c = 3; c--;)
      printf("%u", grid[r][c]);
    printf("\n");
  }
  return 0;
}