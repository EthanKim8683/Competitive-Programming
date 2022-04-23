// start 6:22
// end 8:25
// tries 1

#include <iostream>
#include <cstdio>

using namespace std;

using U = unsigned;
using B = bool;

int main(void) {
#if defined(ETHANKIM8683)
  freopen("hanoi.in", "r", stdin);
#endif // defined(ETHANKIM8683)
  cin.tie(0)->sync_with_stdio(0);
  U n;
  cin >> n;
  B o = !(n & 1);
  n = (1 << n) - 1;
  printf("%u\n", n);
  for (U i = 1; i <= n; i++) {
    const U t = i & -i;
    U a = (i - t) % 3;
    U b = (i + t) % 3;
    if (o) {
      if (a)
        a ^= 3;
      if (b)
        b ^= 3;
    }
    printf("%u %u\n", a + 1, b + 1);
  }
  return 0;
}