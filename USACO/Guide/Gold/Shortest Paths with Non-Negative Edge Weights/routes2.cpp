#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MAX = 1e18;
const I N = 500;

Lli dsts[N][N];

I main(void) {
#ifdef ETHANKIM8683
  freopen("routes2.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m, q;
  cin >> n >> m >> q;
  for (I i = 0; i < n; i++)
    fill_n(dsts[i], n, MAX);
  for (I i = 0; i < n; i++)
    dsts[i][i] = 0;
  while (m--) {
    I a, b;
    Lli c;
    cin >> a >> b >> c;
    a--;
    b--;
    dsts[a][b] = min(dsts[a][b], c);
    dsts[b][a] = min(dsts[b][a], c);
  }
  for (I k = 0; k < n; k++)
    for (I i = 0; i < n; i++)
      for (I j = 0; j < n; j++)
        dsts[i][j] = min(dsts[i][j], dsts[i][k] + dsts[k][j]);
  while (q--) {
    I a, b;
    cin >> a >> b;
    const auto dst = dsts[a - 1][b - 1];
    if (dst == MAX)
      printf("-1\n");
    else
      printf("%lli\n", dst);
  }
  return 0;
}