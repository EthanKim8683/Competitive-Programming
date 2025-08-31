#include <bits/stdc++.h>

#include "ethankim8683/trees.hpp"

using namespace std;

const int MAXP = 2000;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int Q;
  cin >> Q;

  vector<array<int, 4>> queries(Q);
  for (auto &r : queries) {
    cin >> r[0] >> r[1];
    r[1]--;
    for (int i = 2; i < (int[]) {2, 4, 2, 3}[r[0] - 1]; i++) {
      cin >> r[i];
    }
  }

  vector<pair<int, int>> stats = {{}};
  vector<int> end = {0}, len = {0}, par = {0};
  vector<vector<int>> adj = {{}};
  vector<tuple<int, int, int>> queries_;
  int N = 1;
  for (auto [K, X, P, T] : queries) {
    if (K == 1) {
      end.push_back(end[X]);
      len.push_back(len[X]);
    } else if (K == 2) {
      int p = end[X], a = N++;
      end[X] = a;
      len[X]++;

      stats.push_back({P, T});
      adj.push_back({});
      adj[a].push_back(p);
      adj[p].push_back(a);
    } else if (K == 3) {
      len[X]--;
    } else if (K == 4) {
      queries_.push_back({end[X], len[X], P});
    }
  }

  tree_utils tu(adj);
  for (auto &[a, b, P] : queries_) {
    b = b == 0 ? -1 : tu.kth_anc(a, b - 1);
  }

  auto [r, adj_] = centroid_decomp(adj);
  tree_utils tu_(adj_, r);
  vector<vector<int>> by_centroid(N);
  for (int i = 0; i < queries_.size(); i++) {
    auto [a, b, P] = queries_[i];
    if (b == -1) continue;
    by_centroid[tu_.lca(a, b)].push_back(i);
  }

  vector<bool> cut(N, false);
  vector<int> ans(queries_.size(), 0);
  vector dp(N, vector<int>(MAXP + 1));
  auto dfs_ = [&](auto self, int a, int p) -> void {
    for (auto b : adj[a]) {
      if (b == p or cut[b]) continue;
      auto [P, T] = stats[b];
      dp[b] = dp[a];
      for (int i = MAXP - P; i >= 0; i--) {
        dp[b][i + P] = max(dp[b][i + P], dp[b][i] + T);
      }
      self(self, b, a);
    }
  };
  auto dfs = [&](auto self, int a) -> void {
    fill(dp[a].begin(), dp[a].end(), 0);
    dfs_(dfs_, a, -1);

    auto [P, T] = stats[a];
    for (auto i : by_centroid[a]) {
      auto [u, v, P_] = queries_[i];
      for (int j = 0; j <= P_; j++) {
        ans[i] = max(ans[i], dp[u][j] + dp[v][P_ - j]);
      }
      for (int j = 0; j <= P_ - P; j++) {
        ans[i] = max(ans[i], dp[u][j] + T + dp[v][P_ - P - j]);
      }
    }

    cut[a] = true;
    for (auto b : adj_[a]) {
      self(self, b);
    }
  };
  dfs(dfs, r);

  for (auto e : ans) {
    cout << e << '\n';
  }
}
