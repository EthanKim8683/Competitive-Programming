#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 1e5;

I w_arr[N];

I main(void) {
#ifndef ETHANKIM8683
  freopen("lemonade.in", "r", stdin);
  freopen("lemonade.out", "w", stdout);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> w_arr[i];
  sort(w_arr, w_arr + n, greater<I>());
  I cnt = 0;
  for (I i = 0; i < n; i++) {
    const I w = w_arr[i];
    if (w >= cnt)
      cnt++;
  }
  printf("%i\n", cnt);
  return 0;
}