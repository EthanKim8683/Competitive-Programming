#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

using I = int;
using S = string;

const I L = 2000;
const I M = 2000;
const I MOD = 1e9 + 7;

// 1. current index
// 2. x (mod m)
// 3. (len(x) + 1) % 2
// 4. x < upp, x = upp
I dp[L + 1][M][2][2];

pair<I, I> slv(S dgts, I dgt, I mod) {
  fill(&dp[0][0][0][0], &dp[0][0][0][0] + sizeof(dp) / sizeof(I), 0);
  const I len = dgts.size();
  dp[0][0][0][1] = 1;
  for (I i = 0; i < len; i++) {
    const I lim = dgts[i] - '0';
    for (I j = 0; j < mod; j++) {
      (dp[i + 1][(j * 10 + dgt) % mod][0][0] += dp[i][j][1][0]) %= MOD;
      if (dgt < lim)
        (dp[i + 1][(j * 10 + dgt) % mod][0][0] += dp[i][j][1][1]) %= MOD;
      if (dgt == lim)
        (dp[i + 1][(j * 10 + dgt) % mod][0][1] += dp[i][j][1][1]) %= MOD;
      for (I k = 0; k < 10; k++)
        if (k != dgt)
          (dp[i + 1][(j * 10 + k) % mod][1][0] += dp[i][j][0][0]) %= MOD;
      for (I k = 0; k < lim; k++)
        if (k != dgt)
          (dp[i + 1][(j * 10 + k) % mod][1][0] += dp[i][j][0][1]) %= MOD;
      if (lim != dgt)
        (dp[i + 1][(j * 10 + lim) % mod][1][1] += dp[i][j][0][1]) %= MOD;
    }
    if (i > 0)
      for (I j = 1; j < 10; j++)
        if (j != dgt)
          (dp[i + 1][j % mod][1][0] += 1) % MOD;
  }
  I les = 0;
  I equ = 0;
  for (I i = 0; i < 2; i++) {
    (les += dp[len][0][i][0]) %= MOD;
    (equ += dp[len][0][i][1]) %= MOD;
  }
  return {les, equ};
}

I main(void) {
  cin.tie(0)->sync_with_stdio(0);
  I m, d;
  cin >> m >> d;
  S a;
  cin >> a;
  S b;
  cin >> b;
  const auto [b_les, b_equ] = slv(b, d, m);
  const auto [a_les, a_equ] = slv(a, d, m);
  const I res = b_les + b_equ - a_les;
  printf("%i\n", res % MOD + (res < 0) * MOD);
  return 0;
}