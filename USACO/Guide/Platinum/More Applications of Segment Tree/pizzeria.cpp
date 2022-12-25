#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;
using Lli = long long int;

const I N = 2e5;
const Lli MAX = 1e18;
const I LOGN = 18;
const I FIXN = 1 << 18;

I p_arr[N];
Lli segs1[2 * FIXN];
Lli segs2[2 * FIXN];
I n;

void asn1(Lli segs[], I i, I val) {
  segs[i + FIXN] = val;
}

void asn2(I i, I val) {
  asn1(segs1, i, val + n - 1 - i);
  asn1(segs2, i, val + i);
}

void bld1(Lli segs[]) {
  for (I i = FIXN - 1; i > 0; i--)
    segs[i] = min(segs[i << 1], segs[i << 1 | 1]);
}

void bld2() {
  bld1(segs1);
  bld1(segs2);
}

void upd1(Lli segs[], I i, I val) {
  for (segs[i += FIXN] = val; i > 1; i >>= 1)
    segs[i >> 1] = min(segs[i], segs[i ^ 1]);
}

void upd2(I i, I val) {
  upd1(segs1, i, val + n - 1 - i);
  upd1(segs2, i, val + i);
}

Lli qry1(Lli segs[], I l, I r) {
  Lli res = MAX;
  for (l += FIXN, r += FIXN; l < r; l >>= 1, r >>= 1) {
    if (l & 1)
      res = min(res, segs[l++]);
    if (r & 1)
      res = min(res, segs[--r]);
  }
  return res;
}

Lli qry2(I i) {
  return min(qry1(segs1, 0, i + 1) - (n - 1 - i), qry1(segs2, i, n) - i);
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  fill_n(segs1, 2 * FIXN, MAX);
  fill_n(segs2, 2 * FIXN, MAX);
  I q;
  cin >> n >> q;
  for (I i = 0; i < n; i++)
    cin >> p_arr[i];
  for (I i = 0; i < n; i++)
    asn2(i, p_arr[i]);
  bld2();
  while (q--) {
    I typ;
    cin >> typ;
    if (typ == 1) {
      I k, x;
      cin >> k >> x;
      upd2(k - 1, x);
    } else {
      I k;
      cin >> k;
      printf("%lli\n", qry2(k - 1));
    }
  }
  return 0;
}