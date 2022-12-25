#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 2e5;
const I M = 100;
const Lli MOD = 1e9 + 7;

Lli facs[N + 1];
I a_arr[N];

Lli pow(Lli bse, Lli exp) {
  Lli res = 1;
  while (exp) {
    if (exp & 1)
      res = res * bse % MOD;
    bse = bse * bse % MOD;
    exp >>= 1;
  }
  return res;
}

Lli inv(Lli bse) {
  return pow(bse, MOD - 2);
}

Lli bin(I n, I k) {
  Lli res = facs[n];
  res = res * inv(facs[k]) % MOD;
  res = res * inv(facs[n - k]) % MOD;
  return res;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("tuples.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  I t;
  cin >> t;
  facs[0] = 1;
  for (I i = 1; i <= N; i++)
    facs[i] = facs[i - 1] * i % MOD;
  while (t--) {
    I n, m, k;
    cin >> n >> m >> k;
    for (I i = 0; i < n; i++)
      cin >> a_arr[i];
    sort(a_arr, a_arr + n);
    Lli res = 0;
    for (I i = 0; i < n; i++) {
      const I upp = upper_bound(a_arr + i, a_arr + n, a_arr[i] + k) - a_arr;
      if (upp - i >= m)
        res = (res + bin(upp - i - 1, m - 1)) % MOD;
    }
    printf("%lli\n", res);
  }
  return 0;
}