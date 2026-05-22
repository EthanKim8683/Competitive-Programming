#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
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

const double EPSILON = 1e-7;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 2:56
  // thinking done: 3:08
  // target impl time: 10 min
  // initial impl done: 3:14

  int N, M;
  cin >> N >> M;

  vc<vi> adj(N);
  rep(i, 0, M) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].pb(v);
    adj[v].pb(u);
  }

  int X;
  cin >> X;
  X--;

  vc<bool> seen(N, false);
  double ans = 1;
  auto dfs = [&](auto self, int a, int d, float x) -> void {
    if (seen[a]) return;
    seen[a] = true;

    if (a != X) {
      ans += x;
    }

    for (auto b : adj[a]) {
      double x2 = x / sz(adj[b]);
      if (x2 < EPSILON) continue;
      self(self, b, d + 1, x2);
    }

    seen[a] = false;
  };
  dfs(dfs, X, 0, 1);
  cout << setprecision(1) << fixed << ans << '\n';
}
