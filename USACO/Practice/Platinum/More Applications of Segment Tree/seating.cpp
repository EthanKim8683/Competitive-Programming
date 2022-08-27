#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

using I = int;
using C = char;
using B = bool;

const I N = 500000;
const I LOGN = 19;
const I FIXN = 1 << LOGN;

I segs[2 * FIXN];
set<I> begs;

I ith(I i) {
  return segs[i + FIXN];
}

void upd(I i, I val) {
  for (segs[i += FIXN] = val; i > 1; i >>= 1)
    segs[i >> 1] = max(segs[i], segs[i ^ 1]);
}

I qry(I val) {
  I res = 1;
  for (I i = 0; i < LOGN; i++)
    res = res << 1 | (val > segs[res << 1]);
  return res - FIXN;
}

I main(void) {
  freopen("seating.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("seating.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  I res = 0;
  upd(0, n);
  begs.insert(0);
  while (m--) {
    C t;
    cin >> t;
    if (t == 'A') {
      I p;
      cin >> p;
      if (p > segs[1])
        res++;
      else {
        const I beg = qry(p);
        const I len = ith(beg);
        upd(beg, 0);
        begs.erase(beg);
        if (len - p > 0) {
          upd(beg + p, len - p);
          begs.insert(beg + p);
        }
      }
    } else if (t == 'L') {
      I a, b;
      cin >> a >> b;
      I a_beg = a - 1;
      I a_end = b;
      // can't find bug? brute force and pray.
      for (auto it = begs.begin(); it != begs.end();) {
        const auto b_beg = *it;
        const auto b_end = b_beg + ith(b_beg);
        if (b_end >= a_beg && b_beg < a_beg)
          a_beg = b_beg;
        if (b_beg <= a_end && b_end > a_end)
          a_end = b_end;
        if (b_beg >= a_beg && b_beg <= a_end) {
          upd(b_beg, 0);
          it = begs.erase(it);
        } else
          it++;
      }
      upd(a_beg, a_end - a_beg);
      begs.insert(a_beg);
    }
  }
  printf("%i\n", res);
  return 0;
}