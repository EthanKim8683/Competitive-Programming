#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, M;
  cin >> N >> M;

  vector adj(N, vector<bool>(N, false));
  for (int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u][v] = adj[v][u] = true;
  }

  int I = -1, J = -1, k0 = -1;
  vector dp(1 << N, vector<int>(N, 0));
  for (int i = 0; i < N; i++) {
    dp[1 << i][i] |= 1 << i;
  }
  for (int i = 0; i < (1 << N); i++) {
    bool ok = true;
    for (int j_ = i ^ ((1 << N) - 1); j_ != 0; j_ -= j_ & -j_) {
      int j = __lg(j_ & -j_);
      bool found = false;
      for (int k_ = i; k_ != 0; k_ -= k_ & -k_) {
        int k = __lg(k_ & -k_);
        if (!adj[j][k]) continue;
        found = true;
      }
      ok = ok and found;
    }

    for (int j_ = i; j_ != 0; j_ -= j_ & -j_) {
      int j = __lg(j_ & -j_);

      for (int k_ = i ^ ((1 << N) - 1); k_ != 0; k_ -= k_ & -k_) {
        int k = __lg(k_ & -k_);
        if (!adj[j][k]) continue;
        dp[i | 1 << k][k] |= dp[i][j];
      }

      for (int k_ = dp[i][j]; k_ != 0; k_ -= k_ & -k_) {
        int k = __lg(k_ & -k_);
        if (!adj[j][k]) continue;
        if (!ok) continue;
        I = i;
        J = j;
        k0 = k;
        goto FOUND;
      }
    }
  }

  if (I == -1) {
    cout << "No";
    exit(0);
  }

FOUND:
  vector dp2(1 << N, vector<pair<int, int>>(N, {-1, -1}));
  dp2[1 << k0][k0] = {0, -1};
  for (int i = 0; i < (1 << N); i++) {
    for (int j_ = i; j_ != 0; j_ -= j_ & -j_) {
      int j = __lg(j_ & -j_);
      if (dp2[i][j] == make_pair(-1, -1)) continue;
      for (int k_ = i ^ ((1 << N) - 1); k_ != 0; k_ -= k_ & -k_) {
        int k = __lg(k_ & -k_);
        if (!adj[j][k]) continue;
        dp2[i | 1 << k][k] = {i, j};
      }
    }
  }

  vector<int> ans(N, -1);
  int i = I, j = J, pj = k0;
  while (i != 0) {
    ans[j] = pj;
    pj = j;
    tie(i, j) = dp2[i][j];
  }
  for (int i = 0; i < N; i++) {
    if (ans[i] != -1) continue;
    for (int j = 0; j < N; j++) {
      if (!adj[i][j]) continue;
      if (~I >> j & 1) continue;
      ans[i] = j;
    }
  }

  cout << "Yes\n";
  for (auto e : ans) {
    cout << e + 1 << ' ';
  }
}