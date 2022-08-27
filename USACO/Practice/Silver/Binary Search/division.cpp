#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;
using B = bool;

const I N = 2e5;
const Lli MAX = 1e18;

I x_arr[N];
I n, k;

B che(Lli sum) {
  Lli cur = 0;
  I cnt = 1;
  for (I i = 0; i < n; i++) {
    if (x_arr[i] > sum)
      return false;
    if (cur + x_arr[i] > sum) {
      cur = 0;
      cnt++;
    }
    if (cnt > k)
      return false;
    cur += x_arr[i];
  }
  return true;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> k;
  for (I i = 0; i < n; i++)
    cin >> x_arr[i];
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