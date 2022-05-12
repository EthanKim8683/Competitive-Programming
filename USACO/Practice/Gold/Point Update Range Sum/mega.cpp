#include <iostream>
#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class Key, class Compare = less<Key>>
using indexed_set = tree<Key, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

using I = int;
using Lli = long long int;

const I N = 1e5;

I x_arr[N];
Lli frw_arr[N];
Lli bkw_arr[N];
indexed_set<I, greater_equal<I>> frw;
indexed_set<I, less_equal<I>> bkw;

I main(void) {
#ifdef ETHANKIM8683
  freopen("mega.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> x_arr[i];
  for (I i = 0; i < n; i++) {
    const auto x = x_arr[i];
    frw_arr[i] = frw.order_of_key(x);
    frw.insert(x);
  }
  for (I i = n - 1; i >= 0; i--) {
    const auto x = x_arr[i];
    bkw_arr[i] = bkw.order_of_key(x);
    bkw.insert(x);
  }
  Lli res = 0;
  for (I i = 0; i < n; i++)
    res += frw_arr[i] * bkw_arr[i];
  printf("%lli\n", res);
  return 0;
}