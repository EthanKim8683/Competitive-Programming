#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<vector<int>> adj(N);
    for (int i = 1; i < N; i++) {
      int P;
      cin >> P;
      P--;
      adj[P].push_back(i);
    }

    auto dfs = [&](auto self, int a) -> pair<int, int> {
      vector<pair<int, int>> branches;
      int size = 1;
      for (auto b : adj[a]) {
        auto [extrab, sizeb] = self(self, b);
        branches.push_back({extrab, sizeb});
        size += sizeb;
      }
      if (branches.empty()) return {1, 1};

      sort(branches.begin(), branches.end());
      int most = branches.back().first, rest = 0;
      for (int i = 0; i < branches.size() - 1; i++) {
        rest += branches[i].second;
      }
      if (most <= rest) {
        return {1 + (most + rest) % 2, size};
      } else {
        return {1 + most - rest, size};
      }
    };
    cout << (N - dfs(dfs, 0).first) / 2 << '\n';
  }
}