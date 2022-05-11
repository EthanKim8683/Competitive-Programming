#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e5;

Lli segs[2 * N];
I n;

void set(I i, I val) {
  segs[i + n] = val;
}

void bld() {
  for (I i = n - 1; i > 0; i--)
    segs[i] = segs[i << 1] + segs[i << 1 | 1];
}

void upd(I i, I val) {
  for (segs[i += n] = val; i > 1; i >>= 1)
    segs[i >> 1] = segs[i] + segs[i ^ 1];
}

Lli qry(I l, I r) {
  Lli res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1)
      res += segs[l++];
    if (r & 1)
      res += segs[--r];
  }
  return res;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("sum.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I q;
  cin >> n >> q;
  for (I i = 0; i < n; i++) {
    I x;
    cin >> x;
    set(i, x);
  }
  bld();
  while (q--) {
    I t;
    cin >> t;
    if (t == 1) {
      I k, u;
      cin >> k >> u;
      upd(k - 1, u);
    } else if (t == 2) {
      I a, b;
      cin >> a >> b;
      printf("%lli\n", qry(a - 1, b));
    }
  }
  return 0;
}