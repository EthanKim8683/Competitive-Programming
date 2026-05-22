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

  int T, Q;
  cin >> T >> Q;

  if (Q == 1) {
    while (T--) {
      int N, S;
      cin >> N >> S;
      S--;

      vi voltage(N, 0);
      rep(i, 0, N - 1) { voltage[i + 1] = voltage[i] ^ (S >> i & 1); }

      rep(i, 0, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        if (u > v) {
          swap(u, v);
        }
        if ((voltage[u] ^ voltage[v]) == 1) {
          swap(u, v);
        }
        cout << u + 1 << ' ' << v + 1 << endl;
      }
    }
  } else {
    while (T--) {
      int N;
      cin >> N;

      vc<vc<pii>> adj(N);
      rep(i, 0, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        int w = 0;
        if (u > v) {
          w = 1;
        }
        adj[u].eb(v, w);
        adj[v].eb(u, w);
      }

      vi voltage(N);
      auto dfs = [&](auto self, int a, int p, int d) -> void {
        voltage[a] = d;
        for (auto [b, w] : adj[a]) {
          if (b == p) continue;
          self(self, b, a, d ^ w);
        }
      };
      dfs(dfs, 0, -1, 0);

      int ans = 0;
      rep(i, 0, N - 1) { ans |= (voltage[i + 1] ^ voltage[i]) << i; }
      ans += 1;
      cout << ans << endl;
    }
  }
}
