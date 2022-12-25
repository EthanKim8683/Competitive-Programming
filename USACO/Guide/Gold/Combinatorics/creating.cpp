#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;
using C = char;

const I MOD = 1e9 + 7;
const I N = 1e6;

C s[N];
Lli facs[N + 1];
I cnts[26];

Lli pow(Lli bse, I exp) {
  Lli res = 1;
  while (exp) {
    if (exp & 1)
      res = res * bse % MOD;
    exp >>= 1;
    bse = bse * bse % MOD;
  }
  return res;
}

Lli inv(Lli bse) {
  return pow(bse, MOD - 2) % MOD;
}

I main(void) {
#ifdef ETHANKIM8683
  freopen("creating.in", "r", stdin);
#endif
  cin.tie(0)->sync_with_stdio(0);
  cin >> s;
  I len = 0;
  for (I i = 0; i < N; i++) {
    if (!s[i])
      break;
    cnts[s[i] - 'a']++;
    len++;
  }
  facs[0] = 1;
  for (I i = 1; i <= len; i++)
    facs[i] = facs[i - 1] * i % MOD;
  Lli res = facs[len];
  for (I i = 0; i < 26; i++)
    res = res * inv(facs[cnts[i]]) % MOD;
  printf("%lli\n", res);
  return 0;
}