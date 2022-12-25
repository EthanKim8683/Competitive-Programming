#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

using I = int;

const I N = 2e5;
const I M = 2e5;

I h_arr[N];
I t_arr[M];
multiset<I> tcks;

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  for (I i = 0; i < n; i++)
    cin >> h_arr[i];
  for (I i = 0; i < m; i++)
    cin >> t_arr[i];
  for (I i = 0; i < n; i++)
    tcks.insert(h_arr[i]);
  for (I i = 0; i < m; i++) {
    auto it = tcks.upper_bound(t_arr[i]);
    if (it != tcks.begin()) {
      it--;
      printf("%i\n", *it);
      tcks.erase(it);
    } else
      printf("-1\n");
  }
  return 0;
}