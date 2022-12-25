#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e5;

I a_arr[N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, x;
  cin >> n >> x;
  for (I i = 0; i < n; i++)
    cin >> a_arr[i];
  I l = 0;
  I r = 0;
  Lli sum = a_arr[0];
  I res = 0;
  while (r < n) {
    if (sum == x) {
      res++;
      sum += a_arr[++r];
    } else {
      if (l == r)
        sum += a_arr[++r];
      else if (sum > x)
        sum -= a_arr[l++];
      else if (sum < x)
        sum += a_arr[++r];
    }
  }
  printf("%i\n", res);
  return 0;
}