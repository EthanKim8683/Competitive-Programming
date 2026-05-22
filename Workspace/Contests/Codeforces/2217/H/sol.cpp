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

  // i think this is just dp...
  //
  // at each node, choose to swap up or not
  //
  // each node stores which node swapped up (or none)
  //
  // max of
  // sum of children regardless of choice
  // sum of children where a child matches unswapped badge
  // sum of children where a child matches swapped badge
  //
  //
  // ugh nvm annoying impl

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi W(N);
    for (auto &e : W) cin >> e;

    vi A(2 * N);
    for (auto &e : A) cin >> e;

    vc<vi> adj(N);
    rep(i, 0, N - 1) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].pb(v);
      adj[v].pb(u);
    }

    auto dfs = [&](auto self, int a, int p) -> map<int, int> {

    };
  }
}
