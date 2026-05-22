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

const int LOGN = 17;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 6:44
  // thinking done: 6:52
  // target impl time: 20 min
  // initial impl done: 7:16

  int N;
  cin >> N;

  vi C(N);
  for (auto &e : C) {
    cin >> e;
    e--;
  }

  vc<vc<pii>> adj(N);
  rep(i, 0, N - 1) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj[a].eb(b, i);
    adj[b].eb(a, i);
  }

  vc anc(N, vi(LOGN + 1));
  vi tin(N), tout(N);
  int t = 0;
  auto dfs = [&](auto self, int a, int p, int d) -> void {
    anc[a][0] = p;
    tin[a] = t;
    t++;
    for (auto [b, i] : adj[a]) {
      if (b == p) continue;
      self(self, b, a, d + 1);
    }
    tout[a] = t;
  };
  dfs(dfs, 0, 0, 0);
  rep(i, 1, LOGN + 1) {
    rep(j, 0, N) { anc[j][i] = anc[anc[j][i - 1]][i - 1]; }
  }
  auto is_anc = [&](int a, int b) -> bool {
    return tin[a] <= tin[b] and tout[b] <= tout[a];
  };
  auto lca = [&](int a, int b) -> int {
    if (is_anc(a, b)) return a;
    for (int i = LOGN; i >= 0; i--) {
      if (!is_anc(anc[a][i], b)) {
        a = anc[a][i];
      }
    }
    return anc[a][0];
  };

  vc<vi> groups(N);
  rep(i, 0, N) { groups[C[i]].pb(i); }

  vi ps(N, 0);
  vc<vi> adj2(N);
  rep(i, 0, N) {
    if (groups[i].empty()) continue;

    auto less = [&](int a, int b) -> bool { return tin[a] < tin[b]; };
    sort(all(groups[i]), less);

    vi nodes = groups[i];
    rep(j, 0, sz(groups[i]) - 1) {
      nodes.pb(lca(groups[i][j], groups[i][j + 1]));
    }
    sort(all(nodes), less);
    nodes.erase(unique(all(nodes)), nodes.end());

    for (auto e : nodes) {
      adj2[e].clear();
    }
    rep(i, 0, sz(nodes) - 1) {
      adj2[lca(nodes[i], nodes[i + 1])].pb(nodes[i + 1]);
    }

    set<int> S(all(groups[i]));
    auto dfs = [&](auto self, int a) -> int {
      int count = 0;
      if (S.contains(a)) {
        count++;
      }
      for (auto b : adj2[a]) {
        int count2 = self(self, b), contrib = count2 * (sz(S) - count2);
        ps[b] += contrib;
        ps[a] -= contrib;
        count += count2;
      }
      return count;
    };
    dfs(dfs, nodes[0]);
  }

  vi ans(N - 1);
  auto dfs2 = [&](auto self, int a, int p) -> int {
    int sum = ps[a];
    for (auto [b, i] : adj[a]) {
      if (b == p) continue;
      int sum2 = self(self, b, a);
      ans[i] = sum2;
      sum += sum2;
    }
    return sum;
  };
  dfs2(dfs2, 0, -1);

  for (auto e : ans) {
    cout << e << '\n';
  }
}
