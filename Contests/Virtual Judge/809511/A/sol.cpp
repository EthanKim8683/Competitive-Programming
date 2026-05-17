#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/dsu.hpp"
using namespace atcoder;

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

  // components are all size 3
  //
  // no 3 across

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vc<string> grid(N);
    for (auto &e : grid) cin >> e;

    dsu d(N * M);

    vc<pii> deltas1, deltas2;
    rep(i, -1, 1 + 1) {
      if (i == 0) continue;
      deltas1.eb(0, i);
      deltas1.eb(i, 0);
    }
    rep(i, -1, 1 + 1) {
      rep(j, -1, 1 + 1) {
        if (i == 0 and j == 0) continue;
        deltas2.eb(i, j);
      }
    }

    auto encode = [&](int i, int j) -> int { return i * M + j; };

    auto is_inside = [&](int i, int j) -> bool {
      return 0 <= i and i < N and 0 <= j and j < M;
    };

    rep(i, 0, N) {
      rep(j, 0, M) {
        if (grid[i][j] != '*') continue;
        for (auto [di, dj] : deltas1) {
          int i2 = i + di, j2 = j + dj;
          if (!is_inside(i2, j2)) continue;
          if (grid[i2][j2] != '*') continue;
          d.merge(encode(i, j), encode(i2, j2));
        }
      }
    }
    bool ok = true;
    rep(i, 0, N) {
      rep(j, 0, M) {
        if (grid[i][j] == '*') {
          ok = ok and d.size(encode(i, j)) == 3;
        }
        for (auto [di, dj] : deltas2) {
          int i2 = i + di, j2 = j + dj;
          if (!is_inside(i2, j2)) continue;
          ok = ok and d.same(encode(i, j), encode(i2, j2)) ==
                          (grid[i][j] == '*' and grid[i2][j2] == '*');
        }
        bool ok2 = true, ok3 = true;
        rep(k, 0, 3) {
          ok2 = ok2 and is_inside(i, j + k) and grid[i][j + k] == '*';
          ok3 = ok3 and is_inside(i + k, j) and grid[i + k][j] == '*';
        }
        ok = ok and not ok2;
        ok = ok and not ok3;
      }
    }
    cout << (ok ? "YES" : "NO") << '\n';
  }
}
