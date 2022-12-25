#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using B = bool;

const I N = 100000;

I h_arr[N];
I n;

I search_ge(I x) {
  I l = 0;
  I r = n;
  while (l < r) {
    const I m = l + (r - l) / 2;
    if (h_arr[m] < x)
      l = m + 1;
    else
      r = m;
  }
  return l;
}

I search_gt(I x) {
  I l = 0;
  I r = n;
  while (l < r) {
    const I m = l + (r - l) / 2;
    if (h_arr[m] <= x)
      l = m + 1;
    else
      r = m;
  }
  return l;
}

I main(void) {
  freopen("haybales.in", "r", stdin);
#ifndef ETHANKIM8683
  freopen("haybales.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I q;
  cin >> n >> q;
  for (I i = n; i--;)
    cin >> h_arr[i];
  sort(h_arr, h_arr + n);
  while (q--) {
    I a, b;
    cin >> a >> b;
    printf("%i\n", search_gt(b) - search_ge(a));
  }
  return 0;
}