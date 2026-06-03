#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/modint.hpp"
using namespace atcoder;

using mint = modint998244353;

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

  // number of pairs of paths where we visit same characters
  //
  // dp

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

    vi parent(N), depth(N);
    auto dfs = [&](auto self, int a, int p, int d) -> void {
      parent[a] = p;
      depth[a] = d;
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a, d + 1);
      }
    };
    dfs(dfs, 0, -1, 0);

    vi order(N);
    iota(all(order), 0);
    sort(all(order), [&](int a, int b) -> bool { return depth[a] > depth[b]; });

    vi index(N);
    rep(i, 0, N) { index[order[i]] = i; }

    vc dp(4, vc(N, vc<mint>(N, 0)));
    rep(i, 0, N) {
      rep(j, 0, N) {
        mint count = 0;

        if (S[order[i]] == S[order[j]]) {
          count += 1;
          count += dp[1][i][j];
        }

        int p1 = parent[order[i]], p2 = parent[order[j]];
        if (p1 != -1 and p2 != -1) {
          dp[0][index[p1]][index[p2]] += count;
          dp[1][index[p1]][index[p2]] += count;
        }

        dp[2][i][j] += count;
        dp[3][i][j] += count;

        if (p1 != -1) {
          dp[0][index[p1]][j] += dp[0][i][j];
          dp[1][index[p1]][j] += dp[0][i][j];
          dp[2][index[p1]][j] += dp[2][i][j];
          dp[3][index[p1]][j] += dp[2][i][j];
        }

        if (p2 != -1) {
          dp[1][i][index[p2]] += dp[1][i][j];
          dp[3][i][index[p2]] += dp[3][i][j];
        }
      }
    }

    rep(i, 0, N) { cout << dp[3][index[i]][index[i]].val() << ' '; }
    cout << '\n';
  }
}
