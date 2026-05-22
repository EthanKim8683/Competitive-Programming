#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<string> C(N);
  for (auto &e : C) cin >> e;

  vector dp(N, vector<int>(N, INF));
  queue<pair<int, int>> q;
  auto push = [&](int i, int j, int d) -> void {
    if (d >= dp[i][j]) return;
    dp[i][j] = d;
    q.push({i, j});
  };
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (C[i][j] != '-') {
        push(i, j, 1);
      }
    }
    push(i, i, 0);
  }
  while (q.size() > 0) {
    auto [i, j] = q.front();
    q.pop();

    for (int k = 0; k < N; k++) {
      for (int l = 0; l < N; l++) {
        if (C[k][i] != '-' and C[k][i] == C[j][l]) {
          push(k, l, dp[i][j] + 2);
        }
      }
    }
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << (dp[i][j] == INF ? -1 : dp[i][j]) << ' ';
    }
    cout << '\n';
  }
}
