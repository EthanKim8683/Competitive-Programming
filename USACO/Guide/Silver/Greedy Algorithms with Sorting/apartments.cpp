#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 2e5;
const I M = 2e5;

I a_arr[N];
I b_arr[M];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, m, k;
  cin >> n >> m >> k;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  for (I i = 0; i < m; i++)
    cin >> b_arr[i];
  sort(a_arr, a_arr + n);
  sort(b_arr, b_arr + m);
  I res = 0;
  I i = 0;
  I j = 0;
  while (i < n && j < m) {
    const I dif = a_arr[i] - b_arr[j];
    if (abs(dif) <= k) {
      res++;
      i++;
      j++;
    } else if (dif < 0)
      i++;
    else
      j++;
  }
  printf("%i\n", res);
  return 0;
}