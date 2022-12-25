#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 50000;

I x_arr[N];
I n, k;

B check(I r) {
  I ind = 0;
  for (I i = 0; i < k; i++) {
    const I end = x_arr[ind] + r * 2;
    do
      ind++;
    while (ind < n && x_arr[ind] <= end);
    if (ind >= n)
      return true;
  }
  return false;
}

I main(void) {
  freopen("angry.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("angry.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> k;
  for (I i = 0; i < n; i++)
    cin >> x_arr[i];
  sort(x_arr, x_arr + n);
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