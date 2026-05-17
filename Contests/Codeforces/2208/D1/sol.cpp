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

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vc<string> S(N);
    for (auto &e : S) cin >> e;

    // nodes which are reachable by none are roots
    //
    // toposort? a node is adjacent if none of its other children can reach

    vc<vi> adj(N);
    rep(i, 0, N) {
      rep(j, 0, N) {
        if (i == j) continue;
        if (S[i][j] == '0') continue;
        adj[i].pb(j);
      }
    }

    vc<bool> seen(N, false);
    vi order;
    auto dfs = [&](auto self, int a) -> void {
      if (seen[a]) return;
      seen[a] = true;
      for (auto b : adj[a]) {
        self(self, b);
      }
      order.pb(a);
    };
    rep(i, 0, N) { dfs(dfs, i); }
    reverse(all(order));

    vc<vi> adj2(N);
    rep(i, 0, N) {
      rep(j, 0, i) {
        bool is_parent = S[order[j]][order[i]] == '1';
        for (auto e : adj2[order[j]]) {
          is_parent = is_parent and S[e][order[i]] == '0';
        }
        if (!is_parent) continue;
        adj2[order[j]].pb(order[i]);
      }
    }

    int m = 0;
    for (auto r : adj2) {
      m += sz(r);
    }
    if (m != N - 1) {
      cout << "No\n";
      continue;
    }

    vc<vi> adj3(N);
    rep(i, 0, N) {
      for (auto e : adj2[i]) {
        adj3[i].pb(e);
        adj3[e].pb(i);
      }
    }
    fill(all(seen), false);
    auto dfs2 = [&](auto self, int a) -> int {
      if (seen[a]) return 0;
      seen[a] = true;
      int rv = 1;
      for (auto b : adj3[a]) {
        rv += self(self, b);
      }
      return rv;
    };
    if (dfs2(dfs2, 0) != N) {
      cout << "No\n";
      continue;
    }

    vc S2(N, string(N, '0'));
    rep(i, 0, N) {
      auto dfs3 = [&](auto self, int a) -> void {
        S2[i][a] = '1';
        for (auto b : adj2[a]) {
          self(self, b);
        }
      };
      dfs3(dfs3, i);
    }
    if (S2 != S) {
      cout << "No\n";
      continue;
    }

    cout << "Yes\n";
    rep(i, 0, N) {
      for (auto e : adj2[i]) {
        cout << i + 1 << ' ' << e + 1 << '\n';
      }
    }
  }
}
