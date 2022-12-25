#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const I N = 2e5;

I n, k;
I a_arr[N];

B check(I m) {
  Lli ops = 0;
  for (I i = n - 1; i >= n / 2; i--)
    ops += max(0, m - a_arr[i]);
  return ops <= k;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("median.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> k;
  for (I i = n; i--;)
    cin >> a_arr[i];
  sort(a_arr, a_arr + n);
  I l = 0;
  I r = 2e9;
  while (l < r) {
    const I m = l + (r - l + 1) / 2;
    if (check(m))
      l = m;
    else
      r = m - 1;
  }
  printf("%i\n", l);
  return 0;
}