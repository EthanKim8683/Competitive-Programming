#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 100;

I a_arr[N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, x;
  cin >> n >> x;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  sort(a_arr, a_arr + n);
  I sum = 0;
  I res = 0;
  for (I i = 0; i < n; i++) {
    sum += a_arr[i];
    if (sum > x)
      break;
    res++;
  }
  printf("%i\n", res);
  return 0;
}