#include <iostream>
#include <cstdio>

using namespace std;

using I = int;

const I N = 2e5;
const I LOGN = 18;
const I FIXN = 1 << LOGN;

I segs[2 * FIXN];

void asn(I i, I val) {
  segs[i + FIXN] = val;
}

void bld() {
  for (I i = FIXN - 1; i > 0; i--)
    segs[i] = max(segs[i << 1], segs[i << 1 | 1]);
}

void upd(I i, I val) {
  for (segs[i += FIXN] = val; i > 1; i >>= 1)
    segs[i >> 1] = max(segs[i], segs[i ^ 1]);
}

I ith(I i) {
  return segs[i + FIXN];
}

I qry(I val) {
  I res = 1;
  for (I i = 0; i < LOGN; i++)
    res = res << 1 | (val > segs[res << 1]);
  return res - FIXN;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("hotel.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  for (I i = 0; i < n; i++) {
    I h;
    cin >> h;
    asn(i, h);
  }
  bld();
  for (I i = 0; i < m; i++) {
    I r;
    cin >> r;
    if (r <= segs[1]) {
      const auto j = qry(r);
      upd(j, ith(j) - r);
      printf("%i ", j + 1);
    } else
      printf("0 ");
  }
  return 0;
}