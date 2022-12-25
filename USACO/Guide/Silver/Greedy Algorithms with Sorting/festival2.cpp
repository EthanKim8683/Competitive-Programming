#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>

using namespace std;

using I = int;

const I N = 2e5;

pair<I, I> movs[N];
multiset<I> mems;

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, k;
  cin >> n >> k;
  for (I i = 0; i < n; i++) {
    I a, b;
    cin >> a >> b;
    movs[i] = {b, a};
  }
  for (I i = 0; i < k; i++)
    mems.insert(0);
  sort(movs, movs + n);
  I res = 0;
  for (I i = 0; i < n; i++) {
    const auto [b, a] = movs[i];
    auto it = mems.upper_bound(a);
    if (it != mems.begin()) {
      res++;
      mems.erase(--it);
      mems.insert(b);
    }
  }
  printf("%i\n", res);
  return 0;
}