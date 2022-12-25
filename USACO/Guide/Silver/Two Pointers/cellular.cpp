#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;

const I N = 1e5;
const I M = 1e5;

I a_arr[N];
I b_arr[M];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, m;
  cin >> n >> m;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  for (I i = 0; i < m; i++)
    cin >> b_arr[i];
  sort(a_arr, a_arr + n);
  sort(b_arr, b_arr + m);
  I j = 0;
  I res = 0;
  for (I i = 0; i < n; i++) {
    const I a = a_arr[i];
    while (j + 1 < m && b_arr[j + 1] < a)
      j++;
    I dis = abs(b_arr[j] - a);
    if (j + 1 < m)
      dis = min(dis, abs(b_arr[j + 1] - a));
    res = max(res, dis);
  }
  printf("%i\n", res);
  return 0;
}