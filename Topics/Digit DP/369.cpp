#include <iostream>
#include <cstdio>

using namespace std;

using I = int;
using Lli = long long int;
using S = string;

const I L = 51;
const I K = 16;
const Lli MOD = 1e9 + 7;

Lli facs[L + 1];

Lli pow(Lli bse, Lli exp) {
  bse %= MOD;
  Lli res = 1;
  while (exp) {
    if (exp & 1)
      (res *= bse) %= MOD;
    (bse *= bse) %= MOD;
    exp >>= 1;
  }
  return res;
}

Lli inv(Lli val) {
  return pow(val, MOD - 2);
}

Lli bin(Lli n, Lli k) {
  return facs[n] * inv(facs[k] * facs[n - k]) % MOD;
}

pair<Lli, Lli> slv(S upp) {
  Lli res = 0;
  I t = 0;
  I s = 0;
  I n = 0;
  const I len = upp.size();
  for (I i = 0; i < len; i++) {
    const I dgt = upp[i] - '0';
    for (I j = 0; j < dgt; j++) {
      const I t_j = t + (j == 3);
      const I s_j = s + (j == 6);
      const I n_j = n + (j == 9);
      for (I k = max(t_j, max(s_j, max(n_j, 1))); k <= K; k++) {
        I rem = len - (i + 1);
        if (rem - (k - t_j) - (k - s_j) - (k - n_j) < 0)
          break;
        Lli com = 1;
        (com *= bin(rem, k - t_j)) %= MOD;
        rem -= k - t_j;
        (com *= bin(rem, k - s_j)) %= MOD;
        rem -= k - s_j;
        (com *= bin(rem, k - n_j)) %= MOD;
        rem -= k - n_j;
        (com *= pow(7, rem)) %= MOD;
        (res += com) %= MOD;
      }
    }
    t += dgt == 3;
    s += dgt == 6;
    n += dgt == 9;
  }
  return {res, t == s && s == n && t >= 1};
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  facs[0] = 1;
  for (I i = 1; i <= L; i++)
    facs[i] = facs[i - 1] * i % MOD;
  I t;
  cin >> t;
  while (t--) {
    S a, b;
    cin >> a >> b;
    const auto [b_les, b_equ] = slv(b);
    const auto [a_les, a_equ] = slv(a);
    const Lli res = b_les + b_equ - a_les;
    printf("%lli\n", res % MOD + (res < 0) * MOD);
  }
  return 0;
}