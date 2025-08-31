#include <bits/stdc++.h>

#include "atcoder/convolution.hpp"
#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;
using mint = modint998244353;

struct S {
  i64 n;
  vector<mint> dp;
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  i64 N;
  int P, K;
  cin >> N >> P >> K;

  // vector dp(N + 1, vector<mint>(K + 1, 0));
  // dp[0][0] = 1;
  // for (int i = 0; i < N; i++) {
  //   for (int j = 0; j <= i; j++) {
  //     dp[i + 1][j] += dp[i][j] * mint(P).pow(j);
  //     dp[i + 1][j + 1] += dp[i][j] * (mint(P).pow(N) - mint(P).pow(j));
  //   }
  // }
  // for (auto e : dp[N]) {
  //   cout << e.val() << ' ';
  // }

  auto op = [&](S a, S b) -> S {
    mint x = mint(P).pow(b.n), y = 1;
    for (int i = 0; i < a.dp.size(); i++) {
      a.dp[i] *= y;
      y *= x;
    }
    auto dp = convolution(a.dp, b.dp);
    if (dp.size() > K + 1) {
      dp.resize(K + 1);
    }
    return S(a.n + b.n, dp);
  };
  S x(1, vector<mint>(2, 0));
  x.dp[0] = 1;
  x.dp[1] = P;
  S y(1, vector<mint>(1, 0));
  y.dp[0] = 1;
  for (i64 i = N - 1; i; i >>= 1, x = op(x, x)) {
    if (i & 1) {
      y = op(y, x);
    }
  }

  mint f = 1;
  for (int i = 0; i <= K; i++) {
    if (i > N) {
      cout << 0 << ' ';
      continue;
    }

    mint bn = y.dp[i];
    if (i - 1 >= 0) {
      bn += y.dp[i - 1];
    }
    // cout << (f * bn).val() << ' ';
    f *= mint(P).pow(N - i) - 1;
  }
}
