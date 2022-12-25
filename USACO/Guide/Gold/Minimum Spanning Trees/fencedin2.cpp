#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 25000;
const I M = 25000;
const Lli MAX = 1e18;

Lli vers[N + 2];
Lli hors[M + 2];
Lli rows[M + 1];
Lli cols[N + 1];

I main(void) {
  freopen("fencedin.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("fencedin.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I a, b, n, m;
  cin >> a >> b >> n >> m;
  for (I i = 1; i <= n; i++)
    cin >> vers[i];
  for (I i = 1; i <= m; i++)
    cin >> hors[i];
  vers[n + 1] = a;
  hors[m + 1] = b;
  sort(vers, vers + n + 2);
  sort(hors, hors + m + 2);
  for (I i = 0; i <= m; i++)
    rows[i] = hors[i + 1] - hors[i];
  for (I i = 0; i <= n; i++)
    cols[i] = vers[i + 1] - vers[i];
  sort(rows, rows + m + 1);
  sort(cols, cols + n + 1);
  I row_cnt = m;
  I col_cnt = n;
  I row_ind = 1;
  I col_ind = 1;
  Lli res = rows[0] * n + cols[0] * m;
  while (row_cnt > 0 && col_cnt > 0) {
    if (rows[row_ind] < cols[col_ind]) {
      res += rows[row_ind++] * col_cnt;
      row_cnt--;
    } else {
      res += cols[col_ind++] * row_cnt;
      col_cnt--;
    }
  }
  printf("%lli\n", res);
  return 0;
}