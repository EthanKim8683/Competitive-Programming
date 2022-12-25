#include <iostream>
#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class Key, class Compare = less<Key>>
using indexed_set = tree<Key, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

using I = int;

const I N = 2e5;

I x_arr[N];
indexed_set<I> inds;

I main(void) {
#ifdef ETHANKIM8683
  freopen("removals.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++) {
    cin >> x_arr[i];
    inds.insert(i);
  }
  for (I i = 0; i < n; i++) {
    I p;
    cin >> p;
    auto it = inds.find_by_order(p - 1);
    printf("%i ", x_arr[*it]);
    inds.erase(it);
  }
  return 0;
}