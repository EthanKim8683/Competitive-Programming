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

const int K = 1500;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // sqrt decomp?
  //
  // decontribute self
  //
  // if sz(adj[a]) > K, have map<color, relief>
  //
  // else just brute force count
  //
  // recontribute self

  int T;
  cin >> T;

  while (T--) {
    int N, Q;
    cin >> N >> Q;

    vi A(N);
    for (auto &e : A) {
      cin >> e;
      e--;
    }

    vc<vc<pii>> adj(N);
    rep(i, 0, N - 1) {
      int u, v, c;
      cin >> u >> v >> c;
      u--, v--;
      adj[u].eb(v, c);
      adj[v].eb(u, c);
    }

    auto is_heavy = [&](int a) -> bool { return sz(adj[a]) > K; };

    vi sums(N, 0);
    vc<vi> reliefs(N);
    rep(i, 0, N) {
      if (!is_heavy(i)) continue;
      reliefs[i].resize(N);
      for (auto [b, c] : adj[i]) {
        sums[i] += c;
        reliefs[i][A[b]] += c;
      }
    }

    vc<vc<pii>> adj2(N);
    rep(i, 0, N) {
      for (auto [b, c] : adj[i]) {
        if (!is_heavy(b)) continue;
        adj2[i].eb(b, c);
      }
    }

    int ans = 0;
    auto contribute = [&](int a, int d) -> void {
      if (is_heavy(a)) {
        ans += d * (sums[a] - reliefs[a][A[a]]);
      } else {
        for (auto [b, c] : adj[a]) {
          if (A[a] == A[b]) continue;
          ans += d * c;
        }
      }
    };
    rep(i, 0, N) { contribute(i, 1); }
    ans /= 2;
    while (Q--) {
      int v, x;
      cin >> v >> x;
      v--, x--;
      contribute(v, -1);
      for (auto [b, c] : adj2[v]) {
        reliefs[b][A[v]] -= c;
      }
      A[v] = x;
      for (auto [b, c] : adj2[v]) {
        reliefs[b][A[v]] += c;
      }
      contribute(v, 1);
      cout << ans << '\n';
    }
  }
}
