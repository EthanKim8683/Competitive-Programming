#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 500000;
const I LOGN = 19;

I rngs[N][LOGN];
I n;

void bld() {
  for (I i = 1; 1 << i <= n; i++)
    for (I j = 0; j + (1 << (i - 1)) < n; j++)
      rngs[j][i] = min(rngs[j][i - 1], rngs[j + (1 << (i - 1))][i - 1]);
}

I qry(I a, I b) {
  const I len = b - a;
  const I dis = 31 - __builtin_clz(len);
  return min(rngs[a][dis], rngs[b - (1 << dis)][dis]);
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("static.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I q;
  cin >> n >> q;
  for (I i = 0; i < N; i++)
    fill_n(rngs[i], LOGN, 1e9);
  for (I i = 0; i < n; i++)
    cin >> rngs[i][0];
  bld();
  while (q--) {
    I l, r;
    cin >> l >> r;
    printf("%i\n", qry(l, r));
  }
  return 0;
}