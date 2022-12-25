#include <iostream>
#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class Key, class Compare = less<Key>>
using indexed_set = tree<Key, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

using I = int;
using Lli = long long int;

I main(void) {
#ifdef ETHANKIM8683
  freopen("inversion.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    I n;
    cin >> n;
    indexed_set<I, greater_equal<I>> set;
    Lli res = 0;
    for (I i = 0; i < n; i++) {
      I a;
      cin >> a;
      res += set.order_of_key(a);
      set.insert(a);
    }
    printf("%lli\n", res);
  }
  return 0;
}