#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;

const I N = 500;
const I X = 500;
const Lli MOD = 998244353;

Lli dp[X + 1][N + 1];
Lli facs[N + 1];
Lli invs[N + 1];
Lli pows[N + 1][X + 1];

Lli inv(Lli val) {
  val %= MOD;
  Lli exp = MOD - 2;
  Lli res = 1;
  while (exp) {
    if (exp & 1)
      (res *= val) %= MOD;
    (val *= val) %= MOD;
    exp >>= 1;
  }
  return res;
}

Lli pow(I bse, I exp) {
  return pows[bse][exp];
}

Lli bin(I n, I k) {
  Lli res = facs[n];
  (res *= invs[k]) %= MOD;
  (res *= invs[n - k]) %= MOD;
  return res;
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I n, x;
  cin >> n >> x;
  facs[0] = 1;
  for (I i = 1; i <= n; i++)
    (facs[i] = facs[i - 1] * i) %= MOD;
  for (I i = 0; i <= n; i++)
    invs[i] = inv(facs[i]);
  for (I i = 0; i <= x; i++) {
    pows[i][0] = 1;
    for (I j = 1; j <= n; j++)
      pows[i][j] = pows[i][j - 1] * i % MOD;
  }
  dp[1][1] = bin(n, 1);
  for (I i = 1; i <= x; i++) {
    for (I j = 1; j <= n; j++) {
      for (I k = i == 1; j + k <= n; k++) {
        const I dmg = j + k - 1;
        if (i + dmg <= x) {
          Lli com = dp[i][j];
          (com *= bin(n - j, k)) %= MOD;
          (com *= pow(dmg, k)) %= MOD;
          (dp[i + dmg][j + k] += com) %= MOD;
        }
      }
    }
  }
  Lli res = pow(x, n);
  for (I i = 0; i < x; i++) {
    Lli com = dp[x - i][n];
    (com *= i + 1) %= MOD;
    (res -= com) %= MOD;
  }
  printf("%lli\n", res + (res < 0) * MOD);
  return 0;
}