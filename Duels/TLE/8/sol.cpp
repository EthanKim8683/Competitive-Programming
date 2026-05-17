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

  // #
  // ##
  //  ##
  //   #

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vc<string> grid(N);
    for (auto &e : grid) cin >> e;

    auto is_inside = [&](int i, int j) -> bool {
      return 0 <= i and i < N and 0 <= j and j < M;
    };

    bool ok = true;
    vc colors(N, vi(M, 0));
    auto color = [&](int i, int j, int c) -> void {
      if (colors[i][j] != 0) {
        ok = ok and colors[i][j] == c;
        return;
      }
      colors[i][j] = c;
    };

    pii deltas[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    rep(i, 0, N) {
      rep(j, 0, M) {
        if (grid[i][j] != '*') continue;

        vc<pii> adj;
        for (auto [di, dj] : deltas) {
          int i2 = i + di, j2 = j + dj;
          if (!is_inside(i2, j2)) continue;
          if (grid[i2][j2] != '*') continue;
          adj.eb(i2, j2);
        }

        if (sz(adj) == 2) {
          color(i, j, 1);
          for (auto [i2, j2] : adj) {
            color(i2, j2, 2);
          }
        } else if (sz(adj) == 1) {
          color(i, j, 2);
          for (auto [i2, j2] : adj) {
            color(i2, j2, 1);
          }
        } else {
          ok = false;
        }
      }
    }

    auto bad1 = [&](int i, int j) -> bool {
      if (i + 3 > N) return false;
      return grid[i][j] == '#' and grid[i + 1][j] == '#' and
             grid[i + 2][j] == '#';
    };
    auto bad2 = [&](int i, int j) -> bool {
      if (j + 3 > M) return false;
      return grid[i][j] == '#' and grid[i][j + 1] == '#' and
             grid[i][j + 2] == '#';
    };
    auto bad3 = [&](int i, int j) -> bool {
      if (i + 2 > N or j + 2 > M) return false;
      return grid[i][j] != grid[i + 1][j] and grid[i][j] != grid[i][j + 1] and
             grid[i + 1][j + 1] != grid[i + 1][j] and
             grid[i + 1][j + 1] != grid[i][j + 1];
    };
    auto bad4 = [&](int i, int j) -> bool {
      if (i + 3 > N or j + 3 > M) return false;
      return grid[i][j] == '#' and grid[i + 1][j + 1] == '#' and
             grid[i + 2][j + 2] == '#';
    };
    auto bad5 = [&](int i, int j) -> bool {
      if (i + 3 > N or j + 3 > M) return false;
      return grid[i + 2][j] == '#' and grid[i + 1][j + 1] == '#' and
             grid[i][j + 2] == '#';
    };
    bool bad = false;
    rep(i, 0, N) {
      rep(j, 0, M) {
        bad = bad or bad1(i, j);
        bad = bad or bad2(i, j);
        bad = bad or bad3(i, j);
        bad = bad or bad4(i, j);
        bad = bad or bad5(i, j);
      }
    }
    cout << (bad or !ok ? "NO" : "YES") << '\n';
  }
}
