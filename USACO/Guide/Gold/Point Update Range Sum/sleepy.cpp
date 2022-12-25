#include <iostream>
#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template<class Key, class Compare = less<Key>>
using indexed_set = tree<Key, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

using I = int;

const I N = 1e5;

indexed_set<I> vals;
indexed_set<I> ords;
I p_arr[N];

I main(void) {
  freopen("sleepy.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("sleepy.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> p_arr[i];
  I prt = n;
  while (prt > 0) {
    const auto p = p_arr[prt - 1];
    if (vals.order_of_key(p) != 0)
      break;
    prt--;
    vals.insert(p);
  }
  for (I i = prt; i < n; i++)
    ords.insert(p_arr[i]);
  printf("%i\n", prt);
  for (I i = 0; i < prt; i++) {
    const auto p = p_arr[i];
    printf("%i", prt - i + ords.order_of_key(p) - 1);
    if (i + 1 < prt)
      printf(" ");
    ords.insert(p);
  }
  return 0;
}