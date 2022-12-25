#include <iostream>
#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class Key, class Compare = less<Key>>
using indexed_set = tree<Key, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

using I = int;
using C = char;

const I N = 2e5;

I p_arr[N];
indexed_set<I, less_equal<I>> sals;

I main(void) {
#ifdef ETHANKIM8683
  freopen("salary.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, q;
  cin >> n >> q;
  for (I i = 0; i < n; i++) {
    I p;
    cin >> p;
    p_arr[i] = p;
    sals.insert(p);
  }
  while (q--) {
    C t;
    cin >> t;
    if (t == '!') {
      I k, x;
      cin >> k >> x;
      k--;
      sals.erase(sals.find_by_order(sals.order_of_key(p_arr[k])));
      sals.insert(x);
      p_arr[k] = x;
    } else if (t == '?') {
      I a, b;
      cin >> a >> b;
      printf("%i\n", sals.order_of_key(b + 1) - sals.order_of_key(a));
    }
  }
  return 0;
}