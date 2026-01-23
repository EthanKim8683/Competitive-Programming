#include <bits/stdc++.h>

#include "atcoder/convolution.hpp"
#include "atcoder/modint.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

const int MAXL = 5;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M, K;
  cin >> N >> M >> K;

  vector<int> L(K);
  for (auto &e : L) cin >> e;

  vector<vector<int>> A(K);
  for (int i = 0; i < K; i++) {
    A[i].resize(L[i]);
    for (auto &e : A[i]) cin >> e;
  }

  vector<int> counts(MAXL + 1, 0);
  counts[0]++;
  for (auto e : L) {
    for (int i = 1; i <= e; i++) {
      counts[i]++;
    }
  }

  mint base = 1;
  for (auto e : L) {
    base *= fact<mint>(e);
  }

  int l = accumulate(L.begin(), L.end(), 0);
  vector<vector<mint>> dp(MAXL + 2);
  dp[0].resize(N + 1, 0);
  dp[0][l] = base;
  for (int i = 0; i <= MAXL; i++) {
    vector<mint> c(N + 1);
    c[0] = 1;
    for (int j = 1; j <= N; j++) {
      c[j] = binom<mint>(j + counts[i] - 1, counts[i] - 1) * mint(M - i).pow(j);
    }
    dp[i + 1] = convolution(dp[i], c);
    dp[i + 1].resize(N + 1, 0);
  }
  cout << dp[MAXL + 1][N].val() << '\n';
}
