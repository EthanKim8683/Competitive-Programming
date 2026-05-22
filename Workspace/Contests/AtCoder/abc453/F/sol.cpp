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
    int N, K;
    cin >> N >> K;

    vc<vi> adj(N);
    rep(i, 0, N - 1) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].pb(v);
      adj[v].pb(u);
    }

    vi C(K);
    for (auto &e : C) cin >> e;

    vi order(K);
    iota(all(order), 0);
    sort(all(order), [&](int a, int b) -> bool { return C[a] > C[b]; });

    int n = 0;
    rep(i, 0, N) {
      if (sz(adj[i]) != 1) continue;
      n += 1;
    }
    int sum = 0;
    bool flag = false;
    for (auto e : order) {
      if (C[e] < 2) break;
      sum += C[e];
      flag = flag or n - sum == 1;
    }
    if (sum < n) {
      cout << "-1\n";
      continue;
    }

    queue<pii> counts;
    for (auto e : order) {
      counts.emplace(C[e], e);
    }
    vi ans(N, -1);
    auto assign = [&](int i) -> void {
      auto &[count, x] = counts.front();
      ans[i] = x;
      count -= 1;
      if (count == 0) {
        counts.pop();
      }
    };

    if (N == 2) {
      rep(i, 0, 2) { assign(i); }

      for (auto e : ans) {
        cout << e + 1 << ' ';
      }
      cout << '\n';
      continue;
    }

    vi size(N);
    auto dfs = [&](auto self, int a, int p) -> int {
      size[a] = 0;
      if (sz(adj[a]) == 1) {
        size[a] += 1;
      }
      for (auto b : adj[a]) {
        if (b == p) continue;
        size[a] += self(self, b, a);
      }
      return size[a];
    };
    auto dfs2 = [&](auto self, int a, int p, int n) -> int {
      for (auto b : adj[a]) {
        if (b == p) continue;
        if (2 * size[b] > n) {
          return self(self, b, a, n);
        }
      }
      return a;
    };
    int r;
    rep(i, 0, N) {
      if (sz(adj[i]) == 1) continue;
      r = i;
      break;
    }
    r = dfs2(dfs2, r, -1, dfs(dfs, r, -1));
    assert(sz(adj[r]) != 1);

    vi leaves;
    auto dfs3 = [&](auto self, int a, int p) -> int {
      int rv = 0;
      if (sz(adj[a]) == 1) {
        leaves.pb(a);
        rv += 1;
      }
      for (auto b : adj[a]) {
        if (b == p) continue;
        rv += self(self, b, a);
      }
      return rv;
    };
    for (auto e : adj[r]) {
      assert(dfs3(dfs3, e, r) <= n / 2);
    }

    if (flag) {
      assign(r);
    }
    rep(i, 0, n) { assign(leaves[i / 2 + i % 2 * ((n - 1) / 2 + 1)]); }
    rep(i, 0, N) {
      if (ans[i] != -1) continue;
      assign(i);
    }

    for (auto e : ans) {
      cout << e + 1 << ' ';
    }
    cout << '\n';
  }
}
