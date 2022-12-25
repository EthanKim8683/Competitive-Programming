#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e5;
const Lli MAX = 1e18;

I p_arr[N];

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  for (I i = 0; i < n; i++)
    cin >> p_arr[i];
  sort(p_arr, p_arr + n);
  Lli cst = 0;
  I lst = 0;
  for (I i = 0; i < n; i++)
    cst += p_arr[i];
  Lli res = MAX;
  for (I i = 0; i < n; i++) {
    const I p = p_arr[i];
    const Lli dis = p - lst;
    cst += dis * i - dis * (n - i);
    lst = p;
    res = min(res, cst);
  }
  printf("%lli\n", res);
  return 0;
}