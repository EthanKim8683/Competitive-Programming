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

const int LOGN = 18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // get xor distance from node 1
  //
  // they must all be unique
  //
  // get maximum xor for all values [0, N] for node 1

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vc<vc<pii>> adj(N);
    rep(i, 0, M) {
      int a, b, x;
      cin >> a >> b >> x;
      a--, b--;
      adj[a].eb(b, x);
      adj[b].eb(a, x);
    }

    vi dist(N, -1);
    auto dfs = [&](auto self, int a, int d) -> void {
      if (dist[a] != -1) return;
      dist[a] = d;
      for (auto [b, x] : adj[a]) {
        self(self, b, d ^ x);
      }
    };
    dfs(dfs, 0, 0);

    if (N % 2 == 1) {
      cout << "-1\n";
      continue;
    }

    int ans = 0;
    rep(i, 0, N + 1) { ans ^= i; }
    for (auto e : dist) {
      ans ^= e;
    }
    cout << ans << '\n';
  }
}
