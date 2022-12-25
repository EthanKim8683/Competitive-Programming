#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 2e5;

I p_arr[N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, x;
  cin >> n >> x;
  for (I i = 0; i < n; i++)
    cin >> p_arr[i];
  sort(p_arr, p_arr + n);
  I res = 0;
  I l = 0;
  I r = n - 1;
  while (l < r) {
    res++;
    if (p_arr[l] + p_arr[r] <= x) {
      l++;
      r--;
    } else
      r--;
  }
  res += l == r;
  printf("%i\n", res);
  return 0;
}