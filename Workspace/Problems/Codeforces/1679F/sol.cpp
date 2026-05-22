#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "ethankim8683/graphs.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  int M;
  cin >> M;

  vector<pair<int, int>> edges(M);
  for (auto &[u, v] : edges) {
    cin >> u >> v;
  }

  vector can_swap(10, vector<bool>(10, false));
  for (auto [u, v] : edges) {
    can_swap[u][v] = can_swap[v][u] = true;
  }

  // int N_ = 1;
  // for (int i = 0; i < N; i++) {
  //   N_ *= 10;
  // }
  // set<string> S;
  // for (int i = 0; i < N_; i++) {
  //   string s = to_string(i);
  //   while (s.size() < N) {
  //     s = '0' + s;
  //   }
  //   vector<vector<int>> adj(N);
  //   for (int j = 0; j < N; j++) {
  //     for (int k = j + 1; k < N; k++) {
  //       if (!can_swap[s[j] - '0'][s[k] - '0']) {
  //         adj[j].push_back(k);
  //       }
  //     }
  //   }
  //   auto order = toposort(adj, [&](int a, int b) { return s[a] < s[b]; });
  //   string t = "";
  //   for (auto e : order) {
  //     t += s[e];
  //   }
  //   S.insert(t);
  // }
  // cerr << S.size();

  // if a "can't swap" digit came before, this digit may become available
  //
  // maybe we can keep track of available digits?

  vector<int> cant_swap(10);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (!can_swap[i][j]) {
        cant_swap[i] |= 1 << j;
      }
    }
  }
  vector dp(N + 1, vector<mint>(1 << 10, 0));
  dp[0][(1 << 10) - 1] = 1;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < (1 << 10); j++) {
      for (int k = j; k != 0; k -= k & -k) {
        int l = __lg(k & -k);
        dp[i + 1][k | cant_swap[l]] += dp[i][j];
      }
    }
  }
  mint ans = 0;
  for (int i = 0; i < (1 << 10); i++) {
    ans += dp[N][i];
  }
  cout << ans.val();
}
