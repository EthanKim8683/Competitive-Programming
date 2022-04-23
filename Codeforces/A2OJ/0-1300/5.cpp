#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("5.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U y;
  cin >> y;
  while (true) {
    y++;
    const U a = y % 10;
    const U b = y / 10 % 10;
    const U c = y / 100 % 10;
    const U d = y / 1000 % 10;
    if (a != b && a != c && a != d &&
        b != c && b != d &&
        c != d)
      break;
  }
  printf("%u\n", y);
  return 0;
}