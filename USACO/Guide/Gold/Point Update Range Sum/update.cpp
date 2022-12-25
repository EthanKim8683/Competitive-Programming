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

void upd(I l, I r, I val) {
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1)
      segs[l++] += val;
    if (r & 1)
      segs[--r] += val;
  }
}

Lli qry(I i) {
  Lli res = 0;
  for (i += n; i > 0; i >>= 1)
    res += segs[i];
  return res;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("update.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I q;
  cin >> n >> q;
  for (I i = 0; i < n; i++) {
    I x;
    cin >> x;
    set(i, x);
  }
  while (q--) {
    I t;
    cin >> t;
    if (t == 1) {
      I a, b, u;
      cin >> a >> b >> u;
      upd(a - 1, b, u);
    } else if (t == 2) {
      I k;
      cin >> k;
      printf("%lli\n", qry(k - 1));
    }
  }
  return 0;
}