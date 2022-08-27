#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

using I = int;

const I N = 0x10000;

set<I, greater<I>> a_set;
I difs[N - 1];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, k;
  cin >> n >> k;
  a_set.insert(0);
  for (I i = 0; i < n; i++) {
    I a;
    cin >> a;
    a_set.insert((a / 12 + 1) * 12);
  }
  I res = 0;
  I len = 0;
  auto it = a_set.begin();
  I lst = *it++;
  while (it != a_set.end()) {
    const I cur = *it++;
    const I dif = lst - cur - 12;
    difs[len++] = dif;
    res += dif;
    lst = cur;
  }
  sort(difs, difs + len, greater<I>());
  for (I i = 0; i < len && i < k - 1; i++)
    res -= difs[i];
  printf("%i\n", res + 12 * (a_set.size() - 1));
  return 0;
}