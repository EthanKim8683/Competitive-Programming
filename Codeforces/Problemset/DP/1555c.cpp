#include <iostream>
#include <cstdio>

#define M 100000

using namespace std;

using I = int;

I ps[2][M + 1];

I main(void) {
#ifdef ETHANKIM8683
  freopen("1555c.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I m;
    cin >> m;
    for (I i = 0; i < 2; i++) {
      for (I j = 0; j < m; j++) {
        I a;
        cin >> a;
        ps[i][j + 1] = ps[i][j] + a;
      }
    }
    I result = 1e9;
    for (I i = 0; i < m; i++) {
      const I a = ps[1][i] - ps[1][0];
      const I b = ps[0][m] - ps[0][i + 1];
      result = min(result, max(a, b));
    }
    printf("%i\n", result);
  }
  return 0;
}