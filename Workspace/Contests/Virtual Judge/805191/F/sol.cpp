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

  // sum * delta distance
  //
  // obviously pick highest descendant with sibling
  //
  // delta distance is (longest distance outside this child - 1)
  //
  // multiset of distances

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    vc<vi> adj(N);
    rep(i, 0, N - 1) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].pb(v);
      adj[v].pb(u);
    }

    vi bases(N), dist(N), sums(N);
    vc<multimap<int, int>> by_sum(N);
    vc<multiset<int>> dmaxes(N);
    auto dfs = [&](auto self, int a, int p, int d) -> tuple<int, int, int> {
      int sum = A[a], dmax = d, base = 0;
      dist[a] = d;
      for (auto b : adj[a]) {
        if (b == p) continue;
        auto [sum2, dmax2, base2] = self(self, b, a, d + 1);
        by_sum[a].insert({sum2, dmax2});
        dmaxes[a].insert(dmax2);
        sum += sum2;
        chmax(dmax, dmax2);
        base += base2 + sum2;
      }
      sums[a] = sum;
      bases[a] = base;
      return {sum, dmax, base};
    };
    dfs(dfs, 0, -1, 0);

    vi ans(N);
    auto dfs2 = [&](auto self, int a, int p) -> void {
      ans[a] = bases[a];
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a);
        chmax(ans[a], bases[a] - bases[b] + ans[b]);
      }
      for (auto [sum, dmax] : by_sum[a]) {
        dmaxes[a].erase(dmaxes[a].find(dmax));
        if (sz(dmaxes[a]) > 0) {
          chmax(ans[a], bases[a] + (*dmaxes[a].rbegin() - dist[a]) * sum);
        }
        dmaxes[a].insert(dmax);
      }
    };
    dfs2(dfs2, 0, -1);

    for (auto e : ans) {
      cout << e << ' ';
    }
    cout << '\n';
  }
}
