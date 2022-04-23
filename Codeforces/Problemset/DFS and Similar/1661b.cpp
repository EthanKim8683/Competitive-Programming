#include <iostream>
#include <cstdio>

using namespace std;

using I = int;

I main(void) {
#ifdef ETHANKIM8683
  freopen("1661b.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  while (n--) {
    I a;
    cin >> a;
    if (a) {
      I result = 1e9;
      for (I i = 0; i < 15; i++) {
        const I b = a + i;
        result = min(result, i + 15 - __builtin_ctz(b));
      }
      printf("%i ", result);
    } else
      printf("0 ");
  }
  return 0;
}