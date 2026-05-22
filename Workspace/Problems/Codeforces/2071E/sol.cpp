#include <bits/stdc++.h>

#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<mint> P(N);
    for (auto &e : P) {
      int p, q;
      cin >> p >> q;
      e = (mint) p / q;
    }

    vector<pair<int, int>> edges(N - 1);
    vector<vector<int>> adj(N);
    for (auto &[u, v] : edges) {
      cin >> u >> v;
      u--, v--;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    vector<mint> none(N), any(N);
    mint ans = 0, accum = 0;
    for (int i = 0; i < N; i++) {
      none[i] = 1 - P[i];
      for (auto e : adj[i]) {
        none[i] *= P[e];
      }
      any[i] = 0;
      for (auto e : adj[i]) {
        any[i] += none[i] / P[e] * (1 - P[e]);
      }
      ans += any[i] * accum;
      accum += any[i];
    }

    for (auto [u, v] : edges) {
      ans -= any[u] * any[v];
      ans += none[u] / P[v] * none[v] / P[u];
    }

    for (int i = 0; i < N; i++) {
      mint accum1 = 0, accum2 = 0, accum3 = 0;
      for (auto e : adj[i]) {
        ans -= accum1 * any[e];
        ans += accum2 * none[e] / P[i] * (1 - P[i]);
        ans += accum3 * (any[e] - none[e] / P[i] * (1 - P[i])) / P[i] * P[i];
        accum1 += any[e];
        accum2 += none[e] / P[i];
        accum3 += (any[e] - none[e] / P[i] * (1 - P[i])) / P[i];
      }
    }

    cout << ans.val() << '\n';
  }
}
