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

const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // collapse edges

  int V, E;
  cin >> V >> E;

  int ans = -INF;
  vc<map<int, int>> adj(V);
  set<int> bridges;
  auto insert_adj = [&](int a, int b, int s) -> void {
    if (sz(adj[a]) == 2) {
      bridges.erase(a);
    }
    if (adj[a].contains(b)) {
      chmax(ans, adj[a][b] + s);
      chmax(adj[a][b], s);
    } else {
      adj[a][b] = s;
    }
    if (sz(adj[a]) == 2) {
      bridges.insert(a);
    }
  };

  auto erase_adj = [&](int a, int b) -> void {
    if (sz(adj[a]) == 2) {
      bridges.erase(a);
    }
    adj[a].erase(b);
    if (sz(adj[a]) == 2) {
      bridges.insert(a);
    }
  };

  auto insert_edge = [&](int a, int b, int s) -> void {
    insert_adj(a, b, s);
    insert_adj(b, a, s);
  };

  auto erase_edge = [&](int a, int b) -> void {
    erase_adj(a, b);
    erase_adj(b, a);
  };

  rep(i, 0, E) {
    int a, b, s;
    cin >> a >> b >> s;
    a--, b--;
    insert_edge(a, b, s);
  }

  while (sz(bridges) > 0) {
    int a = *bridges.begin();
    auto [b1, s1] = *adj[a].begin();
    erase_edge(a, b1);
    auto [b2, s2] = *adj[a].begin();
    erase_edge(a, b2);
    insert_edge(b1, b2, s1 + s2);
  }
  cout << ans << '\n';
}
