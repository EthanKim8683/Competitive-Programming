#include <iostream>
#include <cstdio>
#include <algorithm>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class Key, class Compare = less<Key>>
using indexed_set = tree<Key, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

using I = int;
using Lli = long long int;

const I N = 100000;

indexed_set<I, greater<I>> vals;
I frw[2][N];
I bkw[2][N];
I segs[N * 2];
I pnts[N];
I n;

void rng_upd(I l, I r, I val) {
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1)
      segs[l++] += val;
    if (r & 1)
      segs[--r] += val;
  }
}

void pnt_upd(I i, I val) {
  pnts[i] += val;
}

I pnt_qry(I i) {
  I res = pnts[i];
  for (i += n; i > 0; i >>= 1)
    res += segs[i];
  return res;
}

Lli slv(I sde) {
  vals.clear();
  fill_n(segs, n * 2, 0);
  fill_n(pnts, n, 0);
  Lli sum = 0;
  for (I i = 0; i < n; i++) {
    const auto b = bkw[sde][frw[!sde][i]];
    const I dis = vals.order_of_key(b);
    pnts[i] = dis;
    sum += dis;
    vals.insert(b);
  }
  Lli res = sum;
  for (I i = 0; i < n - 1; i++) {
    const auto a = bkw[!sde][frw[sde][i]];
    const I dis = pnt_qry(a);
    pnt_upd(a, -dis);
    rng_upd(a + 1, n, 1);
    sum += n - (a + 1) - dis;
    res = min(res, sum);
  }
  return res;
}

I main(void) {
  freopen("mincross.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("mincross.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = 0; i < n; i++) {
    I a;
    cin >> a;
    a--;
    frw[0][i] = a;
    bkw[0][a] = i;
  }
  for (I i = 0; i < n; i++) {
    I b;
    cin >> b;
    b--;
    frw[1][i] = b;
    bkw[1][b] = i;
  }
  printf("%lli\n", min(slv(0), slv(1)));
  return 0;
}