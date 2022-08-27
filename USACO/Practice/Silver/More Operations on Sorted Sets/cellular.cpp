#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 1e5;
const I M = 1e5;
const Lli MAX = 1e18;

Lli a_arr[N];
Lli b_arr[M];
set<Lli> tows;

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  for (I i = 0; i < m; i++)
    cin >> b_arr[i];
  for (I i = 0; i < m; i++)
    tows.insert(b_arr[i]);
  Lli res = 0;
  for (I i = 0; i < n; i++) {
    const Lli a = a_arr[i];
    auto it = tows.upper_bound(a);
    Lli rad = MAX;
    if (it != tows.end())
      rad = min(rad, abs(a - *it));
    if (it != tows.begin())
      rad = min(rad, abs(a - *--it));
    res = max(res, rad);
  }
  printf("%lli\n", res);
  return 0;
}