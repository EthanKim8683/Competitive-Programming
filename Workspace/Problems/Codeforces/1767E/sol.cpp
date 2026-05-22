#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector<int> C(N);
  for (auto &e : C) cin >> e, e--;

  vector<int> X(M);
  for (auto &e : X) cin >> e;

  // there cannot be two adjacent un-activated platforms

  if (M == 1) {
    cout << X[0];
    exit(0);
  }

  vector<i64> bad(M, 0);
  for (int i = 0; i + 1 < N; i++) {
    bad[C[i]] |= 1ll << C[i + 1];
    bad[C[i + 1]] |= 1ll << C[i];
  }

  auto chmin = [&](i64 &a, i64 b) -> void { a = min(a, b); };

  vector<i64> dp(1 << (M / 2), INF);
  for (int i = (1 << (M / 2)) - 1; i >= 0; i--) {
    i64 sum = 0, mask = 0;
    for (int j = 0; j < M / 2; j++) {
      if (i >> j & 1) {
        sum += X[j];
      } else {
        mask |= bad[j];
      }
    }
    if ((~i & mask & ((1 << (M / 2)) - 1)) == 0) {
      chmin(dp[i], sum);
    }
    for (int j = 0; j < M / 2; j++) {
      if (~i >> j & 1) continue;
      chmin(dp[i ^ 1 << j], dp[i]);
    }
  }

  i64 ans = INF;
  for (int i = 0; i < (1 << (M - M / 2)); i++) {
    i64 sum = 0, mask = 1ll << C[0] | 1ll << C[N - 1];
    for (int j = 0; j < M - M / 2; j++) {
      if (i >> j & 1) {
        sum += X[M / 2 + j];
      } else {
        mask |= bad[M / 2 + j];
      }
    }
    if (~i & (mask >> (M / 2))) continue;
    chmin(ans, sum + dp[mask & ((1 << (M / 2)) - 1)]);
  }
  cout << ans;
}
