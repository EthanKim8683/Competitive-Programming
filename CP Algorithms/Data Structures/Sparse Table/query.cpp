#include <iostream>
#include <cstdio>

using namespace std;

using I = int;

const I N = 100000;
const I LOGN = 17;

I sprs[N][LOGN];
I n;

void asn(I i, I val) {
  sprs[i][0] = val;
}

void bld() {
  for (I i = 1; i < LOGN; i++)
    for (I j = 0, k = 1 << (i - 1); k < n; j++, k++)
      sprs[j][i] = min(sprs[j][i - 1], sprs[k][i - 1]);
}

I qry(I l, I r) {
  const I dis = 31 - __builtin_clz(r - l);
  return min(sprs[l][dis], sprs[r - (1 << dis)][dis]);
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = 0; i < n; i++) {
    I a;
    cin >> a;
    asn(i, a);
  }
  bld();
  I q;
  cin >> q;
  while (q--) {
    I i, j;
    cin >> i >> j;
    printf("%i\n", qry(i, j + 1));
  }
  return 0;
}