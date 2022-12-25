#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 1e5;

I a_arr[N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, t;
  cin >> n >> t;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  I l = 0;
  I r = 0;
  Lli sum = a_arr[l];
  I res = sum <= t;
  while (l < r || r < n - 1) {
    if (r == n - 1)
      sum -= a_arr[l++];
    else if (l == r)
      sum += a_arr[++r];
    else if (sum > t)
      sum -= a_arr[l++];
    else if (sum <= t)
      sum += a_arr[++r];
    if (sum <= t)
      res = max(res, r - l + 1);
  }
  printf("%i\n", res);
  return 0;
}