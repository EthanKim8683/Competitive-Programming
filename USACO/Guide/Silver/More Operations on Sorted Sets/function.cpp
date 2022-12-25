#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

using I = int;
using B = bool;
using Lli = long long int;

const I N = 1e5;
const I M = 1e5;
const Lli MAX = 1e18;

Lli b_ps[M + 1];
set<Lli> b_sums;

B odd(I i) {
  return i & 1;
}

I flp(I i) {
  return odd(i) ? -1 : 1;
}

Lli qry(Lli a_sum) {
  Lli res = MAX;
  auto it = b_sums.upper_bound(a_sum);
  if (it != b_sums.end())
    res = min(res, abs(*it - a_sum));
  if (it-- != b_sums.begin())
    res = min(res, abs(*it - a_sum));
  return res;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("function.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, m, q;
  cin >> n >> m >> q;
  Lli a_sum = 0;
  for (I i = 0; i < n; i++) {
    I a;
    cin >> a;
    a_sum += a * flp(i);
  }
  Lli b_sum = 0;
  for (I i = 0; i < m; i++) {
    I b;
    cin >> b;
    b_ps[i + 1] = b_sum += b * flp(i);
  }
  for (I i = 0; i <= m - n; i++)
    b_sums.insert((b_ps[i + n] - b_ps[i]) * flp(i));
  printf("%lli\n", qry(a_sum));
  for (I i = 0; i < q; i++) {
    I l, r, x;
    cin >> l >> r >> x;
    if (odd(r - l + 1))
      a_sum -= flp(l) * x;
    printf("%lli\n", qry(a_sum));
  }
  return 0;
}