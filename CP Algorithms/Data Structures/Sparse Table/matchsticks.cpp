#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lf = double;

const I N = 1e5;
const I LOGN = 17;

I max_sprs[N][LOGN];
I min_sprs[N][LOGN];
I n;

void asn(I i, I val) {
  max_sprs[i][0] = val;
  min_sprs[i][0] = val;
}

void bld() {
  for (I i = 1; i < LOGN; i++) {
    for (I j = 0, k = 1 << (i - 1); k < n; j++, k++) {
      max_sprs[j][i] = max(max_sprs[j][i - 1], max_sprs[k][i - 1]);
      min_sprs[j][i] = min(min_sprs[j][i - 1], min_sprs[k][i - 1]);
    }
  }
}

I max_qry(I a, I b) {
  if (a >= b)
    return 0;
  const I dis = 31 - __builtin_clz(b - a);
  return max(max_sprs[a][dis], max_sprs[b - (1 << dis)][dis]);
}

I min_qry(I l, I r) {
  if (r >= l)
    return 0;
  const I dis = 31 - __builtin_clz(r - l);
  return min(min_sprs[l][dis], min_sprs[r - (1 << dis)][dis]);
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = 0 ; i < n; i++) {
    I a;
    cin >> a;
    asn(i, a);
  }
  bld();
  I q;
  cin >> q;
  while (q--) {
    I l, r;
    cin >> l >> r;
    r++;
    const Lf frw = min_qry(l, r);
    const Lf bth = max_qry(l, r);
    const Lf bkw = max(max_qry(0, l), max_qry(r, n));
    printf("%.1lf\n", max(frw + bkw, (frw + bth) / 2));
  }
  return 0;
}