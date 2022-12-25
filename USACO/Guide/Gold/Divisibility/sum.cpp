#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MOD = 1e9 + 7;

Lli rng(Lli min, Lli max) {
  Lli cnt = max - min + 1;
  Lli rng = min + max;
  if (cnt & 1)
    rng /= 2;
  else
    cnt /= 2;
  return (cnt % MOD) * (rng % MOD) % MOD;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("sum.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  Lli n;
  cin >> n;
  Lli rot = 0;
  Lli res = 0;
  for (Lli i = 1; i * i <= n; i++) {
    const Lli j = n / i;
    if (j != i) {
      const Lli l = j - n / (i + 1);
      res = (res + i * rng(j - l + 1, j)) % MOD;
      res = (res + l * rng(1, i)) % MOD;
    }
    rot = i;
  }
  res = (res + rot * rng(1, rot)) % MOD;
  printf("%lli\n", res);
  return 0;
}