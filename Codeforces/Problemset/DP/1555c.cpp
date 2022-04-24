#include <iostream>
#include <cstdio>

#define M 100000

using namespace std;

using I = int;

I matrix[M][2];
I dp[M][2][2];

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
    const I l = m - 1;
    for (I i = 0; i < 2; i++)
      for (I j = 0; j < m; j++)
        cin >> matrix[j][i];
    for (I i = 0; i < m - 1; i++) {
      const I j = i + 1;
    }
  }
  return 0;
}