#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 500000;
const Lli MOD = 998244353;

pair<Lli, Lli> segs[2 * N];
I n;

pair<Lli, Lli> cmb(pair<Lli, Lli>& f0, pair<Lli, Lli>& f1) {
  const auto [a0, b0] = f0;
  const auto [a1, b1] = f1;
  return {(a1 * a0) % MOD, (a1 * b0 + b1) % MOD};
}

void asn(I i, Lli a, Lli b) {
  segs[i + n] = {a, b};
}

void bld() {
  for (I i = n - 1; i > 0; i--)
    segs[i] = cmb(segs[i << 1], segs[i << 1 | 1]);
}

void upd(I i, Lli a, Lli b) {
  for (segs[i += n] = {a, b}; i > 1; i >>= 1)
    segs[i >> 1] = cmb(segs[i & ~1], segs[i | 1]);
}

Lli qry(I l, I r, Lli x) {
  pair<Lli, Lli> lft = {1, 0}, rgt = {1, 0};
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1)
      lft = cmb(lft, segs[l++]);
    if (r & 1)
      rgt = cmb(segs[--r], rgt);
  }
  const auto [a, b] = cmb(lft, rgt);
  return (a * x + b) % MOD;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I q;
  cin >> n >> q;
  for (I i = 0; i < n; i++) {
    I a, b;
    cin >> a >> b;
    asn(i, a, b);
  }
  bld();
  while (q--) {
    I t;
    cin >> t;
    if (t == 0) {
      I p, c, d;
      cin >> p >> c >> d;
      upd(p, c, d);
    } else if (t == 1) {
      I l, r, x;
      cin >> l >> r >> x;
      printf("%lli\n", qry(l, r, x));
    }
  }
  return 0;
}