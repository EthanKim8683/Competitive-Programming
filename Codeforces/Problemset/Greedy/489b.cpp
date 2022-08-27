#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 100;
const I M = 100;

I a_arr[N];
I b_arr[M];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  I m;
  cin >> m;
  for (I i = 0; i < m; i++)
    cin >> b_arr[i];
  sort(a_arr, a_arr + n);
  sort(b_arr, b_arr + m);
  I i = 0;
  I j = 0;
  I res = 0;
  while (i < n && j < m) {
    const I a = a_arr[i];
    const I b = b_arr[j];
    if (a - b > 1)
      j++;
    else if (b - a > 1)
      i++;
    else {
      res++;
      i++;
      j++;
    }
  }
  printf("%i\n", res);
  return 0;
}