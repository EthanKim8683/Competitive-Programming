#include <iostream>
#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class Key, class Compare = less<Key>>
using indexed_set = tree<Key, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

using I = int;
using Lli = long long int;

const I N = 100000;

I h_arr[N];
indexed_set<I, greater_equal<I>> frw_set;
indexed_set<I, greater_equal<I>> bkw_set;
I frw_cnts[N];
I bkw_cnts[N];

I main(void) {
  freopen("bphoto.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("bphoto.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> h_arr[i];
  for (I i = 0; i < n; i++) {
    const auto h = h_arr[i];
    frw_cnts[i] = frw_set.order_of_key(h);
    frw_set.insert(h);
  }
  for (I i = n - 1; i >= 0; i--) {
    const auto h = h_arr[i];
    bkw_cnts[i] = bkw_set.order_of_key(h);
    bkw_set.insert(h);
  }
  Lli res = 0;
  for (I i = 0; i < n; i++) {
    const auto frw = frw_cnts[i];
    const auto bkw = bkw_cnts[i];
    res += max(frw, bkw) > 2 * min(frw, bkw);
  }
  printf("%lli\n", res);
  return 0;
}