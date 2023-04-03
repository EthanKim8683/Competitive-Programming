#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e5;

I p_arr[N];
Lli ps[N + 1];

I main(void) {
#ifdef ETHANKIM8683
  freopen("b.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n, q;
  cin >> n >> q;
  for (I i = 0; i < n; i++)
    cin >> p_arr[i];
  sort(p_arr, p_arr + n, greater<I>());
  for (I i = 0; i < n; i++)
    ps[i + 1] = ps[i] + p_arr[i];
  while (q--) {
    I x, y;
    cin >> x >> y;
    printf("%lli\n", ps[x] - ps[x - y]);
  }
  return 0;
}