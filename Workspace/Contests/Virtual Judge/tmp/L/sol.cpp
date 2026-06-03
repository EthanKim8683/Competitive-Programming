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

  // paths
  //
  // K has to be even
  //
  // sum of (cc size)/2 must be at least K/2
  //
  // tree-ify

  int N, M, K;
  cin >> N >> M >> K;

  vc<pii> edges(M);
  for (auto &[u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }

  vc<vc<pii>> adj(N);
  rep(i, 0, M) {
    auto [u, v] = edges[i];
    adj[u].eb(v, i);
    adj[v].eb(u, i);
  }
  vc<bool> seen(N, false);
  vi cc, usable;
  auto dfs = [&](auto self, int a) -> void {
    if (seen[a]) return;
    seen[a] = true;
    cc.pb(a);
    for (auto [b, i] : adj[a]) {
      self(self, b);
    }
  };
  rep(i, 0, N) {
    if (seen[i]) continue;
    cc.clear();
    dfs(dfs, i);
    for (int j = 0; j + 2 <= sz(cc); j += 2) {
      usable.pb(cc[j]);
      usable.pb(cc[j + 1]);
    }
  }
  if (!(K % 2 == 0 and K <= sz(usable))) {
    cout << "No\n";
    exit(0);
  }
  vc<bool> used(N, false);
  rep(i, 0, K) { used[usable[i]] = true; }
  fill(all(seen), false);
  vi ans;
  auto dfs2 = [&](auto self, int a) -> int {
    if (seen[a]) return 0;
    seen[a] = true;
    int rv = 0;
    if (used[a]) {
      rv ^= 1;
    }
    for (auto [b, i] : adj[a]) {
      int d = self(self, b);
      if (d == 1) {
        ans.pb(i);
      }
      rv ^= d;
    }
    return rv;
  };
  rep(i, 0, N) { dfs2(dfs2, i); }
  cout << "Yes\n";
  cout << sz(ans) << '\n';
  for (auto e : ans) {
    cout << e + 1 << ' ';
  }
  cout << '\n';
}
