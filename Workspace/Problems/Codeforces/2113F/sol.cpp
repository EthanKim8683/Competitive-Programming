#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    // vector<int> A(N);
    // for (auto &e : A) cin >> e, e--;

    // vector<int> B(N);
    // for (auto &e : B) cin >> e, e--;

    vector M(2, vector<int>(N));
    for (auto &r : M) {
      for (auto &e : r) {
        cin >> e;
        e--;
      }
    }

    vector<vector<pair<int, int>>> occurrences(2 * N);
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < N; j++) {
        occurrences[M[i][j]].push_back({i, j});
      }
    }

    vector<vector<int>> adj(4 * N);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
          adj[4 * i + 2 * j + k].push_back(4 * i + 2 * (j ^ 1) + (k ^ 1));
        }
      }
    }
    for (int i = 0; i < 2 * N; i++) {
      if (occurrences[i].size() <= 1) continue;
      auto [i1, j1] = occurrences[i][0];
      auto [i2, j2] = occurrences[i][1];
      for (int j = 0; j < 2; j++) {
        adj[4 * j1 + 2 * i1 + j].push_back(4 * j2 + 2 * i2 + (j ^ 1));
        adj[4 * j2 + 2 * i2 + j].push_back(4 * j1 + 2 * i1 + (j ^ 1));
      }
    }

    vector ans(2, vector<int>(N, -1));
    auto dfs = [&](auto self, int a) -> void {
      int i = a / 4, j = a % 4 / 2, k = a % 2;
      if (ans[k][i] != -1) return;
      ans[k][i] = M[j][i];
      for (auto b : adj[a]) {
        self(self, b);
      }
    };
    for (int i = 0; i < 4 * N; i++) {
      dfs(dfs, i);
    }

    for (int i = 0; i < N; i++) {
      if (ans[0][i] != -1) continue;
      ans[0][i] = M[0][i];
      ans[1][i] = M[1][i];
    }

    int sum = 0;
    for (auto r : ans) {
      set<int> R;
      for (auto e : r) {
        R.insert(e);
      }
      sum += R.size();
    }

    cout << sum << '\n';
    for (auto r : ans) {
      for (auto e : r) {
        cout << e + 1 << ' ';
      }
      cout << '\n';
    }
  }
}