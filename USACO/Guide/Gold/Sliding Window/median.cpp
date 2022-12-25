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
indexed_set<pair<I, I>> vals;
I k;

I med() {
  return vals.find_by_order(k / 2 - (k % 2 == 0))->first;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("median.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n >> k;
  for (I i = 0; i < n; i++)
    cin >> x_arr[i];
  for (I i = 0; i < k; i++)
    vals.insert({x_arr[i], i});
  printf("%i ", med());
  for (I i = 0; i + k < n; i++) {
    vals.erase(vals.find({x_arr[i], i}));
    vals.insert({x_arr[i + k], i + k});
    printf("%i ", med());
  }
  return 0;
}