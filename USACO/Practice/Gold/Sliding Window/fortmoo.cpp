#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using C = char;

const I N = 200;
const I M = 200;

C cels[N][M + 1];
I ps1[N + 1][M];
I ps2[N][M + 1];

I main(void) {
#ifndef ETHANKIM8683
  freopen("fortmoo.in", "r", stdin);
  freopen("fortmoo.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  for (I i = 0; i < n; i++)
    cin >> cels[i];
  for (I i = 0; i < n; i++) {
    for (I j = 0; j < m; j++) {
      if (cels[i][j] == 'X') {
        ps1[i + 1][j] = 1;
        ps2[i][j + 1] = 1;
      }
    }
  }
  for (I i = 1; i <= n; i++)
    for (I j = 0; j < m; j++)
      ps1[i][j] += ps1[i - 1][j];
  for (I i = 0; i < n; i++)
    for (I j = 1; j <= m; j++)
      ps2[i][j] += ps2[i][j - 1];
  I res = 0;
  for (I i = 0; i < n; i++) {
    for (I j = i; j < n; j++) {
      I low = -1;
      for (I k = 0; k < m; k++) {
        if (ps1[j + 1][k] - ps1[i][k] == 0) {
          if (low == -1 || ps2[i][k + 1] - ps2[i][low] != 0 || ps2[j][k + 1] - ps2[j][low] != 0)
            low = k;
          res = max(res, (j - i + 1) * (k - low + 1));
        }
      }
    }
  }
  printf("%i\n", res);
  return 0;
}