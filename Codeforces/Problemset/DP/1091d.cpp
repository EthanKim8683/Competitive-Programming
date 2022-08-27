#include <iostream>
#include <cstdio>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MOD = 998244353;

// 1   + 0    ((1 - 1) * 1)
// 2   + 0    ((1 - 1) * 2)
// 6   + 3    ((2 - 1) * 3)
// 24  + 32   ((9 - 1) * 4)
// 120 + 275  ((56 - 1) * 5)
// 720 + 2364 ((395 - 1) * 6)

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n;
  cin >> n;
  Lli fac = 1;
  Lli res = 1;
  for (Lli i = 1; i <= n; i++) {
    fac = fac * i % MOD;
    res = ((res - 1) * i + fac) % MOD;
  }
  printf("%lli\n", res);
  return 0;
}