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

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    auto length = [&](int k) -> int {
      int rv = 1 + k * (k + 1) / 2;
      if (k % 2 == 0) {
        rv -= k / 2 - 1;
      }
      return rv;
    };

    int k = 1;
    while (length(k) < N) {
      k += 1;
    }

    vi labels(k);
    labels[0] = 1;
    rep(i, 1, k) { labels[i] = labels[i - 1] * 3; }
    rep(i, 0, k) { labels[i] <<= k - 1 - i; }

    map<int, set<int>> adj;
    rep(i, 0, k) {
      rep(j, i, k) {
        if (k % 2 == 0) {
          if (i >= 2 and (i ^ j) == 1) continue;
        }
        int a = labels[i], b = labels[j];
        adj[a].insert(b);
        adj[b].insert(a);
      }
    }

    vi order;
    auto dfs = [&](auto self, int a) -> void {
      while (sz(adj[a]) > 0) {
        int b = *adj[a].begin();
        adj[a].erase(b);
        adj[b].erase(a);
        self(self, b);
      }
      order.pb(a);
    };
    dfs(dfs, labels[0]);
    order.resize(N);

    for (auto e : order) {
      cout << e << ' ';
    }
    cout << '\n';
  }
}
