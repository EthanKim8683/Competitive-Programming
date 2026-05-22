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

const int LOGW = 30;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int N, M, K;
    cin >> N >> M >> K;

    vc<vc<pii>> adj(N);
    rep(i, 0, M) {
      int u, v, w;
      cin >> u >> v >> w;
      u--, v--;
      adj[u].eb(v, w);
      adj[v].eb(u, w);
    }

    vi bases(LOGW, -1);
    auto insert = [&](int x) -> void {
      for (int i = LOGW - 1; i >= 0; i--) {
        if ((x >> i & 1) == 0) continue;
        if (bases[i] == -1) {
          bases[i] = x;
          break;
        }
        x ^= bases[i];
      }
    };
    auto normalize = [&](int &x) -> void {
      for (int i = LOGW - 1; i >= 0; i--) {
        if ((x >> i & 1) == 0) continue;
        if (bases[i] == -1) continue;
        x ^= bases[i];
      }
    };

    vc trie(1, vi(2, -1));
    vi counts(1, 0);
    auto insert2 = [&](int x) -> void {
      auto dfs = [&](auto self, int a, int i) -> void {
        if (i == -1) {
          counts[a] += 1;
          return;
        }

        for (auto e : trie[a]) {
          if (e == -1) continue;
          counts[a] -= counts[e];
        }

        int j = x >> i & 1;
        if (trie[a][j] == -1) {
          trie[a][j] = sz(trie);
          trie.eb(2, -1);
          counts.pb(0);
        }
        self(self, trie[a][j], i - 1);

        for (auto e : trie[a]) {
          if (e == -1) continue;
          counts[a] += counts[e];
        }
      };
      dfs(dfs, 0, LOGW - 1);
    };
    auto count = [&](int x) -> int {
      int a = 0, rv = 0;
      for (int i = LOGW - 1; i >= 0; i--) {
        if (a == -1) break;
        int lt = -1, eq = -1;
        rep(j, 0, 2) {
          int x2 = (x >> i & 1) ^ j, K2 = K >> i & 1;
          if (x2 < K2) {
            lt = trie[a][j];
          } else if (x2 == K2) {
            eq = trie[a][j];
          }
        }
        if (lt != -1) {
          rv += counts[lt];
        }
        a = eq;
      }
      if (a != -1) {
        rv += counts[a];
      }
      return rv;
    };

    vi dist(N, -1);
    auto dfs = [&](auto self, int a, int p) -> void {
      for (auto [b, w] : adj[a]) {
        if (b == p) continue;
        if (dist[b] == -1) {
          dist[b] = dist[a] ^ w;
          self(self, b, a);
        } else {
          insert(dist[a] ^ w ^ dist[b]);
        }
      }
    };
    dist[0] = 0;
    dfs(dfs, 0, -1);

    int ans = 0;
    for (auto e : dist) {
      normalize(e);
      ans += count(e);
      insert2(e);
    }
    cout << ans << '\n';
  }
}
