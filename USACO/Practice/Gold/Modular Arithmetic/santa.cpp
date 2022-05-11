#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MOD = 998244353;
const I K = 1e6;
const I A = 1e6;

I a_arr[K];
Lli prbs[A];

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

I main(void) {
#ifdef ETHANKIM8683
  freopen("santa.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  Lli n;
  cin >> n;
  I len = 0;
  const Lli sqr = n * n % MOD;
  for (I i = 0; i < n; i++) {
    Lli k;
    cin >> k;
    const Lli prb = inv(k * sqr % MOD);
    for (I j = 0; j < k; j++) {
      I a;
      cin >> a;
      a--;
      prbs[a] = (prbs[a] + prb) % MOD;
      a_arr[len] = a;
      len++;
    }
  }
  Lli res = 0;
  for (I i = 0; i < len; i++)
    res = (res + prbs[a_arr[i]]) % MOD;
  printf("%lli\n", res);
  return 0;
}