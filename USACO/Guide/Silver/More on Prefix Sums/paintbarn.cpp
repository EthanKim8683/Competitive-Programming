#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using I = int;

I ps[1001][1001];

int main(void) {
  freopen("paintbarn.in", "r", stdin);
#if !defined(ETHANKIM8683)
  freopen("paintbarn.out", "w", stdout);
#endif // !defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n, k;
  cin >> n >> k;
  while (n--) {
    U x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    x1++;
    y1++;
    x2++;
    y2++;
    ps[y1][x1]++;
    ps[y1][x2]--;
    ps[y2][x1]--;
    ps[y2][x2]++;
  }
  U result = 0;
  for (U y = 1; y <= 1000; y++) {
    for (U x = 1; x <= 1000; x++) {
      ps[y][x] += ps[y - 1][x] + ps[y][x - 1] - ps[y - 1][x - 1];
      result += ps[y][x] == k;
    }
  }
  printf("%u\n", result);
}