#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // all leaves are red
  //
  // now pick root

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    string S;
    cin >> S;

    vc<vi> adj(N);
    rep(i, 0, N - 1) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].pb(v);
      adj[v].pb(u);
    }

    double ans = 0;
    auto dfs = [&](auto self, int a, int p) -> pair<bool, double> {
      if (S[a] == '1') {
        for (auto b : adj[a]) {
          if (b == p) continue;
          auto [found2, ex2] = self(self, b, a);
          if (found2) {
            ans += ex2;
          }
        }
        return {true, 0};
      } else {
        bool found = false;
        double ex = 0;
        int x = 0;
        for (auto b : adj[a]) {
          if (b == p) continue;
          auto [found2, ex2] = self(self, b, a);
          if (found2) {
            found = true;
            chmin(ex, ex2);
          } else {
            x += 1;
          }
        }
        if (found) {
          double ev1 = (double) sz(adj[a]) / (sz(adj[a]) - x - 1),
                 ev2 = (double) sz(adj[a]) / (sz(adj[a]) - x);
          ans += ev1;
          chmin(ex, ev2 - ev1);
        } else {
          double ev = (double) sz(adj[a]) / 1;
          ans += ev;
        }
        return {found, ex};
      }
    };
    dfs(dfs, find(all(S), '1') - S.begin(), -1);
    cout << setprecision(20) << fixed << ans << '\n';
  }
}
