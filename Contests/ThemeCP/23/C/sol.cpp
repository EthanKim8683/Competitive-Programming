#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const int MAXM = 500;
const i64 MOD = 998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<i64> fact(2 * MAXM + 1);
  fact[0] = 1;
  for (int i = 1; i <= 2 * MAXM; i++) {
    fact[i] = fact[i - 1] * i % MOD;
  }

  auto mod_pow = [&](i64 x, i64 y) -> i64 {
    i64 rv = 1;
    for (x %= MOD; y; y >>= 1, (x *= x) %= MOD) {
      if (y & 1) {
        (rv *= x) %= MOD;
      }
    }
    return rv;
  };

  auto mod_inv = [&](i64 x) -> i64 { return mod_pow(x, MOD - 2); };

  auto binom = [&](int n, int k) -> i64 {
    i64 rv = 1;
    (rv *= fact[n]) %= MOD;
    (rv *= mod_inv(fact[k])) %= MOD;
    (rv *= mod_inv(fact[n - k])) %= MOD;
    return rv;
  };

  auto bertrand = [&](int p, int q) -> i64 {
    i64 rv = 1;
    (rv *= binom(p + q, p)) %= MOD;
    (rv *= p + 1 - q) %= MOD;
    (rv *= mod_inv(p + 1)) %= MOD;
    return rv;
  };

  vector bertrand_cache(MAXM + 1, vector<i64>(MAXM + 1));
  for (int i = 0; i <= MAXM; i++) {
    for (int j = 0; j <= MAXM; j++) {
      bertrand_cache[i][j] = bertrand(i, j);
    }
  }

  int N, M;
  cin >> N >> M;

  vector dp(N + 1, vector<i64>(M + 1, 0));
  for (int i = 0; 2 * i <= M; i++) {
    (dp[1][M - 2 * i] += bertrand_cache[M - i][i]) %= MOD;
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= M; j++) {
      for (int k = 0; 2 * k <= M; k++) {
        if (!(j - (M - 2 * k) >= 0)) continue;
        (dp[i + 1][j - (M - 2 * k)] += dp[i][j] * bertrand_cache[M - k][k]) %=
            MOD;
      }
    }
  }
  cout << dp[N][0];
}