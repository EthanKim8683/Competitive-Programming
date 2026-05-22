#ifndef L
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

template <class T>
struct RMQ {
  vc<vc<T>> jmp;
  RMQ(const vc<T> &V) : jmp(1, V) {
    for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
      jmp.eb(sz(V) - pw * 2 + 1);
      rep(j, 0, sz(jmp[k])) jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(int a, int b) {
    assert(a < b);
    int dep = 31 - __builtin_clz(b - a);
    return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 4:51
  // thinking done: 4:59
  // target impl time: 15 min
  // initial impl done: 5:05

  // small to large merging?

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

    RMQ rmq(A);
    auto dfs = [&](auto self, int a, int p, int d) -> map<int, int> {
      map<int, int> rv;
      rv[d] = rmq.query(0, d + 1);

      for (auto b : adj[a]) {
        if (b == p) continue;

        auto depths = self(self, b, a, d + 1);

        if (sz(rv) < sz(depths)) {
          rv.swap(depths);
        }
        for (auto [d2, sum] : depths) {
          rv[d2] = min(rv[d2] + sum, rmq.query(d2 - d, d2 + 1));
        }
      }
      return rv;
    };
    int ans = 0;
    for (auto [d, sum] : dfs(dfs, 0, -1, 0)) {
      ans += sum;
    }
    cout << ans << '\n';
  }
}
