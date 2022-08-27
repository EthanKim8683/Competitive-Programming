#include <iostream>
#include <cstdio>

using namespace std;

using I = int;

const I N = 50000;
const I LOGN = 16;

I sprs[N][LOGN];
I n;

void asn(I i, I val) {
  sprs[i][0] = val;
}

I val(I i) {
  return sprs[i][0];
}

void bld() {
  for (I i = 1; i < LOGN; i++)
    for (I j = 0, k = 1 << (i - 1); k < n; j++, k++)
      sprs[j][i] = max(sprs[j][i - 1], sprs[k][i - 1]);
}

I qry(I l, I r) {
  const I dis = 31 - __builtin_clz(r - l);
  return max(sprs[l][dis], sprs[r - (1 << dis)][dis]);
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I m;
  cin >> n >> m;
  for (I i = 0; i < n; i++) {
    I a;
    cin >> a;
    asn(i, a);
  }
  bld();
  I res = 0;
  while (m--) {
    I a, b;
    cin >> a >> b;
    if (a > b)
      swap(a, b);
    a--;
    b--;
    res += !(qry(a, b) > val(a));
  }
  printf("%i\n", res);
  return 0;
}