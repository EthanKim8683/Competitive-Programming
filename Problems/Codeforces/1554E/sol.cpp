#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/algebra.hpp"
#include "ethankim8683/combinatorics.hpp"

using namespace std;
using namespace atcoder;

using u32 = unsigned;
using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; i++) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    auto solve = [&](int k) -> bool {
      bool rv = true;
      auto dfs = [&](auto self, int a, int p) -> int {
        int v = 0;
        for (auto b : adj[a]) {
          if (b == p) continue;
          v += self(self, b, a);
        }
        int d = (v + 1) % k;
        rv = rv and (d == 0 or d == 1);
        return d;
      };
      int d = dfs(dfs, 0, -1);
      rv = rv and d == 1;
      return rv;
    };

    auto F = factorize((u32) N - 1);
    map<int, int> _counts;
    for (auto p : F) {
      _counts[p]++;
    }
    vector<pair<int, int>> counts(_counts.begin(), _counts.end());
    vector<mint> ans(N + 1, 0);
    auto dfs = [&](auto self, int i, int v) -> void {
      if (i == counts.size()) {
        if (v > 1) {
          ans[v] = solve(v);
        }
        return;
      }
      auto [p, c] = counts[i];
      for (int j = 0; j <= c; j++) {
        self(self, i + 1, v);
        v *= p;
      }
    };
    dfs(dfs, 0, 1);

    ans[1] = mint(2).pow(N - 1);
    for (int i = N; i >= 1; i--) {
      for (int j = 2 * i; j <= N; j += i) {
        ans[i] -= ans[j];
      }
    }

    for (int k = 1; k <= N; k++) {
      cout << ans[k].val() << ' ';
    }
    cout << '\n';
  }
}
