#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second
typedef pair<int, int> pii;
typedef vc<int> vi;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 11:15
  // thinking done: 11:26
  // target impl time: 10 min
  // initial impl done: 11:38

  // one blue, one red
  // each color can only form a chain
  // either it's a node, an edge, a triangle, or a square

  int N, M;
  cin >> N >> M;

  vc adj(2, vc<set<int>>(N));
  rep(i, 0, M) {
    int u, v, c;
    cin >> u >> v >> c;
    u--, v--;
    adj[c][u].insert(v);
    adj[c][v].insert(u);
  }

  int ans = 0;

  vc<vi> subsets;
  set<int> seen;
  auto dfs = [&](auto self, int a, int p) -> void {
    if (seen.contains(a)) return;
    seen.insert(a);

    subsets.emplace_back(all(seen));

    if (sz(seen) + 1 <= 4) {
      for (auto b : adj[0][a]) {
        if (b == p) continue;
        self(self, b, a);
      }
    }

    seen.erase(a);
  };
  rep(i, 0, N) { dfs(dfs, i, -1); }
  sort(all(subsets));
  subsets.erase(unique(all(subsets)), subsets.end());

  for (auto subset : subsets) {
    set<int> seen;
    auto dfs = [&](auto self, int a) -> void {
      if (!binary_search(all(subset), a)) return;

      if (seen.contains(a)) return;
      seen.insert(a);

      for (auto b : adj[1][a]) {
        self(self, b);
      }
    };
    dfs(dfs, subset[0]);
    if (sz(seen) == sz(subset)) {
      ans++;
    }
  }

  cout << ans << '\n';
}
