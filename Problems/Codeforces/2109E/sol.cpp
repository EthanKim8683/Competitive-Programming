#include <bits/stdc++.h>

#include "atcoder/modint"
#include "ethankim8683/combinatorics"

using namespace std;
using namespace atcoder;
using mint = modint998244353;

const int MAXN = 500;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  vector<mint> fact(MAXN + 1), ifact(MAXN + 1);
  fact[0] = ifact[0] = 1;
  for (int i = 1; i <= MAXN; i++) {
    fact[i] = fact[i - 1] * i;
    ifact[i] = ifact[i - 1] / i;
  }

  auto binom = [&](int n, int k) -> mint {
    if (n < 0 or k < 0 or n - k < 0) return 0;
    return fact[n] * ifact[k] * ifact[n - k];
  };

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    string S;
    cin >> S;

    vector dp(N + 1, vector<mint>(K + 1, 0));
    dp[0][0] = 1;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j <= K; j++) {
        dp[i + 1][j] += dp[i][j];
        int k_ = j + 1 - (S[N - 1 - i] == '1' ? 1 : 0);
        for (int k = 1; j + k <= K and k <= k_; k++) {
          dp[i + 1][j + k] += dp[i][j] * binom((k_ - k) / 2 + k, k);
        }
      }
    }
    cout << dp[N][K].val() << '\n';
  }
}