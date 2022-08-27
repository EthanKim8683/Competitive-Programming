#include <iostream>
#include <cstdio>

using namespace std;

using I = int;

const I N = 100;

I main(void) {
#ifdef ETHANKIM8683
  freopen("a.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I n, m;
    cin >> n >> m;
    I sum = 0;
    for (I i = 0; i < n; i++) {
      I a;
      cin >> a;
      sum += a;
    }
    printf("%i\n", max(sum - m, 0));
  }
  return 0;
}