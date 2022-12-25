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

indexed_set<I, greater_equal<I>> viss;
I a_arr[N];
Lli invs[N];
Lli ress[N];

I main(void) {
  freopen("haircut.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("haircut.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  Lli res = 0;
  for (I i = 0; i < n; i++) {
    I a;
    cin >> a;
    const auto inv = viss.order_of_key(a);
    invs[a] += inv;
    res += inv;
    viss.insert(a);
  }
  for (I i = n - 1; i >= 0; i--) {
    res -= invs[i];
    ress[i] = res;
  }
  for (I i = 0; i < n; i++)
    printf("%lli\n", ress[i]);
  return 0;
}