#include <bits/stdc++.h>

#include <algorithm>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, K;
  cin >> N >> K;

  vector<int> P(N * K);
  for (auto &e : P) {
    cin >> e;
    e--;
  }

  auto solve = [&](vector<int> cycle) -> int {
    if (cycle.empty()) return 0;

    int K = cycle.size();

    vector<int> chain;
    for (auto e : cycle) {
      chain.push_back(e);
    }
    for (auto e : cycle) {
      chain.push_back(e);
    }

    map<int, vector<int>> indices;
    for (int i = 0; i < chain.size(); i++) {
      indices[chain[i] % N].push_back(i);
    }

    auto chmax = [&](int &a, int b) -> void { a = max(a, b); };

    vector dp(K + 1, vector<int>(2 * K, -INF));
    for (int i = 0; i < 2 * K; i++) {
      dp[1][i] = 0;
    }
    for (int i = 2; i <= K; i++) {
      for (int j = 0; j + i <= 2 * K; j++) {
        chmax(dp[i][j], dp[i - 1][j + 1]);
        for (auto k : indices[chain[j] % N]) {
          if (k <= j or k >= j + i) continue;
          chmax(dp[i][j], dp[k - j][j] + dp[i - (k - j)][k] + 1);
        }
      }
    }
    return *max_element(dp[K].begin(), dp[K].end());
  };

  vector<bool> seen(N * K, false);
  int ans = 0;
  for (int i = 0; i < N * K; i++) {
    vector<int> cycle;
    for (int j = i; !seen[j]; seen[j] = true, j = P[j]) {
      cycle.push_back(j);
    }
    ans += solve(cycle);
  }
  cout << ans << '\n';
}