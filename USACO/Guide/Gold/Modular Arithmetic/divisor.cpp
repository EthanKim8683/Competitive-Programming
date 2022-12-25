#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const Lli MOD = 1e9 + 7;
const I N = 1e5;

pair<I, I> facs[N];
Lli l_pp[N];
Lli r_pp[N];
I n;

Lli pow(Lli bse, Lli exp, Lli mod) {
  Lli res = 1;
  while (exp) {
    if (exp & 1)
      res = res * bse % mod;
    exp >>= 1;
    bse = bse * bse % mod;
  }
  return res;
}

Lli inv(Lli bse, Lli mod) {
  return pow(bse, mod - 2, mod);
}

void pp_bld(Lli mod) {
  l_pp[0] = 1;
  for (I i = 0; i < n - 1; i++)
    l_pp[i + 1] = l_pp[i] * (facs[i].second + 1) % mod;
  r_pp[n - 1] = 1;
  for (I i = n - 1; i > 0; i--)
    r_pp[i - 1] = r_pp[i] * (facs[i].second + 1) % mod;
}

Lli pp_qry(I i, Lli mod) {
  return l_pp[i] * r_pp[i] % mod;
}

Lli pow_rng(Lli bse, Lli exp, Lli mod) {
  return (pow(bse, exp + 1, mod) - 1) * inv(bse - 1, mod) % mod;
}

Lli add_rng(Lli bse, Lli mod) {
  Lli cnt = bse;
  Lli sum = bse + 1;
  if (sum % 2 == 0)
    sum /= 2;
  else
    cnt /= 2;
  return cnt * sum % mod;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("divisor.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> n;
  for (I i = 0; i < n; i++) {
    I x, k;
    cin >> x >> k;
    facs[i] = {x, k};
  }
  pp_bld(MOD - 1);
  Lli num = 1;
  Lli sum = 1;
  Lli prd = 1;
  for (I i = 0; i < n; i++) {
    const auto [x, k] = facs[i];
    num = num * (k + 1) % MOD;
    sum = sum * pow_rng(x, k, MOD) % MOD;
    prd = prd * pow(x, pp_qry(i, MOD - 1) * add_rng(k, MOD - 1) % (MOD - 1), MOD) % MOD;
  }
  printf("%lli\n%lli\n%lli\n", num, sum, prd);
  return 0;
}