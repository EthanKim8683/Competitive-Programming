#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 1e5;

I t_arr[N];
I n, m, c;

B check(I w) {
  I ind = 0;
  for (I i = m; i--;) {
    if (ind >= n)
      break;
    const I beg = t_arr[ind];
    ind++;
    for (I j = c; --j;) {
      if (ind >= n)
        break;
      const I cur = t_arr[ind];
      if (cur - beg > w)
        break;
      ind++;
    }
  }
  return ind == n;
}

I main(void) {
  freopen("convention.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("convention.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m >> c;
  for (I i = n; i--;)
    cin >> t_arr[i];
  sort(t_arr, t_arr + n);
  I l = 0;
  I r = 1e9;
  while (l < r) {
    const I m = l + (r - l) / 2;
    if (check(m))
      r = m;
    else
      l = m + 1;
  }
  printf("%i\n", l);
  return 0;
}