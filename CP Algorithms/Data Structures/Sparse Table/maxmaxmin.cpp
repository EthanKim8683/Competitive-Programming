#include <iostream>
#include <cstdio>

using namespace std;

using I = int;

const I MAX = 1e9;
const I MIN = -1e9;
const I N = 1e5;
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
  I k;
  cin >> n >> k;
  I res;
  if (k == 1) {
    res = MAX;
    for (I i = 0; i < n; i++) {
      I a;
      cin >> a;
      res = min(res, a);
    }
  } else if (k > 2) {
    res = MIN;
    for (I i = 0; i < n; i++) {
      I a;
      cin >> a;
      res = max(res, a);
    }
  } else {
    for (I i = 0; i < n; i++) {
      I a;
      cin >> a;
      asn(i, a);
    }
    bld();
    res = MIN;
    for (I i = 1; i < n; i++)
      res = max(res, max(qry(0, i), qry(i, n)));
  }
  printf("%i\n", res);
  return 0;
}