#ifndef L
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

const int INF = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M;
  cin >> N >> M;

  vc<vi> adj(N);
  rep(i, 0, M) {
    int K;
    cin >> K;

    int a;
    rep(j, 0, K) {
      int b;
      cin >> b;
      b--;

      if (j >= 1) {
        adj[a].pb(b);
        adj[b].pb(a);
      }

      a = b;
    }
  }

  vc dist(N, vi(N, INF));
  rep(i, 0, N) { dist[i][i] = 0; }
  rep(i, 0, N) {
    for (auto b : adj[i]) {
      dist[i][b] = dist[b][i] = 1;
    }
  }
  rep(k, 0, N) {
    rep(i, 0, N) {
      rep(j, 0, N) { chmin(dist[i][j], dist[i][k] + dist[k][j]); }
    }
  }

  vc<set<int>> S(N);
  auto get_subsets = [&](int i, int a) -> vc<pair<int, set<int>>> {
    vi dist2(N, INF);
    for (auto e : S[i]) {
      chmin(dist2[e], dist[a][e]);
      for (auto b : adj[a]) {
        if (S[i].find(b) == S[i].end()) continue;
        chmin(dist2[e], dist[b][e]);
      }
    }

    vc<pair<int, set<int>>> rv;
    for (auto b : adj[a]) {
      if (S[i].find(b) == S[i].end()) continue;
      set<int> Sb;
      for (auto e : S[i]) {
        if (dist[b][e] == dist2[e]) {
          Sb.insert(e);
        }
      }
      rv.eb(b, Sb);
    }
    return rv;
  };

  auto dfs = [&](auto self, int i, int a) -> int {
    for (auto [b, Sb] : get_subsets(i, a)) {
      if (sz(Sb) > sz(S[i]) / 2) return self(self, i, b);
    }
    return a;
  };

  vc<map<int, int>> adj2(N);
  auto dfs2 = [&](auto self, int a) -> int {
    auto Sa = S[a];
    a = dfs(dfs, a, a);
    S[a] = Sa;
    for (auto [b, Sb] : get_subsets(a, a)) {
      S[b] = Sb;
      adj2[a][b] = self(self, b);
    }
    return a;
  };
  rep(i, 0, N) { S[0].insert(i); }
  int r = dfs2(dfs2, 0);

  auto query = [&](int u) -> int {
    cout << u + 1 << endl;
    string t;
    cin >> t;
    if (t == "FOUND") return -1;
    int w;
    cin >> w;
    w--;
    return w;
  };

  rep(i, 0, N) {
    int a = r;
    while (true) {
      int c = query(a);
      if (c == -1) break;
      assert(adj2[a].find(c) != adj2[a].end());
      a = adj2[a][c];
    }
  }
}
