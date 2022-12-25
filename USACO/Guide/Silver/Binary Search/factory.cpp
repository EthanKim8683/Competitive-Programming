#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const I N = 2e5;
const Lli MAX = 1e18;

I k_arr[N];
I n, t;

B che(Lli tim) {
  Lli tot = 0;
  for (I i = 0; i < n; i++) {
    tot += tim / k_arr[i];
    if (tot >= t)
      return true;
  }
  return false;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> t;
  for (I i = 0; i < n; i++)
    cin >> k_arr[i];
  Lli l = 0;
  Lli r = MAX;
  while (l < r) {
    const Lli m = l + (r - l) / 2;
    if (che(m))
      r = m;
    else
      l = m + 1;
  }
  printf("%lli\n", l);
  return 0;
}