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
    int N, M;
    cin >> N >> M;

    vi L(N);
    for (auto &e : L) cin >> e;

    vi R(N);
    for (auto &e : R) cin >> e;

    vc<vc<pii>> adj(N);
    rep(i, 0, M) {
      int x, y, z;
      cin >> x >> y >> z;
      x--, y--;
      adj[x].eb(y, z);
      adj[y].eb(x, z);
    }

    bool ok = true;
    int ans = 0;
    vi A(N), color(N, 0);
    rep(i, 0, N) {
      if (color[i] != 0) continue;
      vi cc;
      auto dfs = [&](auto self, int a, int x, int y) -> int {
        if (color[a] != 0) {
          if (color[a] == y) {
            return -1;
          } else {
            A[a] = (A[a] + x) / 2;
            return a;
          }
        }
        A[a] = x;
        color[a] = y;
        cc.pb(a);
        for (auto [b, w] : adj[a]) {
          int r = self(self, b, w - x, 3 - y);
          if (r != -1) return r;
        }
        return -1;
      };
      int r = dfs(dfs, i, 0, 1);
      if (r == -2) {
        ok = false;
        break;
      }
      if (r != -1) {
        cc.clear();
        auto dfs2 = [&](auto self, int a, int x) -> void {
          if (color[a] == 3) return;
          A[a] = x;
          color[a] = 3;
          cc.pb(a);
          for (auto [b, w] : adj[a]) {
            self(self, b, w - x);
          }
        };
        dfs2(dfs2, r, A[r]);
        for (auto e : cc) {
          if (L[e] <= A[e] and A[e] <= R[e]) {
            ans += 1;
          }
        }
      } else {
        map<int, int> deltas;
        for (auto e : cc) {
          if (color[e] == 1) {
            deltas[L[e] - A[e]] += 1;
            deltas[R[e] - A[e] + 1] -= 1;
          } else {
            deltas[A[e] - R[e]] += 1;
            deltas[A[e] - L[e] + 1] -= 1;
          }
        }
        int ps = 0, psmax = 0;
        for (auto [x, delta] : deltas) {
          ps += delta;
          chmax(psmax, ps);
        }
        ans += psmax;
      }
    }
    rep(i, 0, N) {
      for (auto [b, w] : adj[i]) {
        ok = ok and A[i] + A[b] == w;
      }
    }
    if (!ok) {
      cout << "-1\n";
    } else {
      cout << ans << '\n';
    }
  }
}
