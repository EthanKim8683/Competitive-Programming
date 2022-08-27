#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using B = bool;

const I N = 8000;

I a_arr[N];
I n;

B fnd(I a) {
  I l = 0;
  I r = 1;
  I sum = a_arr[l] + a_arr[r];
  if (sum == a)
    return true;
  while (l < r - 1 || r < n - 1) {
    if (r == n - 1)
      sum -= a_arr[l++];
    else if (l == r - 1)
      sum += a_arr[++r];
    else if (sum > a)
      sum -= a_arr[l++];
    else if (sum < a)
      sum += a_arr[++r];
    if (sum == a)
      return true;
  }
  return false;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  while (t--) {
    cin >> n;
    for (I i = 0; i < n; i++)
      cin >> a_arr[i];
    if (n >= 2) {
      I res = 0;
      for (I i = 0; i < n; i++)
        res += fnd(a_arr[i]);
      printf("%i\n", res);
    } else
      printf("0\n");
  }
  return 0;
}