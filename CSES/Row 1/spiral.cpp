// start 9:02
// end 9:09
// tries 

#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using Llu = long long unsigned;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("spiral.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U t;
  cin >> t;
  while (t--) {
    Llu y, x;
    cin >> y >> x;
    const Llu m = max(y, x);
    const Llu d = m * m - m + 1;
    const Llu s = (m & 1) * 2 - 1;
    if (y == m)
      printf("%llu\n", d - (m - x) * s);
    else
      printf("%llu\n", d + (m - y) * s);
  }
  return 0;
}