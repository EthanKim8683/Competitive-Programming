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

  // start: 7:43
  // thinking done: 7:44
  // target impl time: 15 min
  // initial impl time: 7:57

  // binary search

  int N, M, K;
  cin >> N >> M >> K;

  vc<pii> obstructions(K);
  for (auto &[i, j] : obstructions) {
    cin >> i >> j;
    i--, j--;
  }

  pii deltas[] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

  vc ps(N + 1, vi(M + 1, 0));
  for (auto [i, j] : obstructions) {
    ps[i + 1][j + 1] += 1;
  }
  rep(i, 1, N + 1) {
    rep(j, 1, M + 1) {
      ps[i][j] += ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1];
    }
  }
  auto sum = [&](int i1, int j1, int i2, int j2) -> int {
    assert(0 <= i1 and i1 <= i2 and i2 <= N and 0 <= j1 and j1 <= j2 and
           j2 <= M);
    return ps[i2][j2] - ps[i2][j1] - ps[i1][j2] + ps[i1][j1];
  };

  auto check = [&](int x) -> bool {
    auto can_clean = [&](int i, int j) -> bool {
      if (!(0 <= i and i + x <= N and 0 <= j and j + x <= M)) return false;
      return sum(i, j, i + x, j + x) == 0;
    };

    vc seen(N, vc<bool>(M, false));
    vc ps(N + 1, vi(M + 1, 0));
    auto fill = [&](int i1, int j1, int i2, int j2) -> void {
      ps[i1][j1] += 1;
      ps[i1][j2] -= 1;
      ps[i2][j1] -= 1;
      ps[i2][j2] += 1;
    };
    auto dfs = [&](auto self, int i, int j) -> void {
      if (!can_clean(i, j)) return;
      if (seen[i][j]) return;
      seen[i][j] = true;
      fill(i, j, i + x, j + x);
      for (auto [di, dj] : deltas) {
        self(self, i + di, j + dj);
      }
    };
    rep(i, 0, N + 1 - x) {
      rep(j, 0, M + 1 - x) {
        if (!can_clean(i, j)) continue;
        dfs(dfs, i, j);
        goto CLEANED;
      }
    }
  CLEANED:
    rep(i, 0, N) {
      rep(j, 0, M) {
        if (i - 1 >= 0) {
          ps[i][j] += ps[i - 1][j];
        }
        if (j - 1 >= 0) {
          ps[i][j] += ps[i][j - 1];
        }
        if (i - 1 >= 0 and j - 1 >= 0) {
          ps[i][j] -= ps[i - 1][j - 1];
        }
      }
    }
    for (auto [i, j] : obstructions) {
      ps[i][j] += 1;
    }
    bool rv = true;
    rep(i, 0, N) {
      rep(j, 0, M) { rv = rv and ps[i][j] > 0; }
    }
    return rv;
  };
  int l = 0, r = min(N, M);
  while (l < r) {
    int m = l + (r - l + 1) / 2;
    check(m) ? l = m : r = m - 1;
  }
  cout << (l == 0 ? -1 : l) << '\n';
}
