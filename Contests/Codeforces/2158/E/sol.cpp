#pragma GCC optimize("Ofast,unroll-loops")
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

const int MAXA = 20;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main(signed argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[1]));
  }

  int T;
  if (argc > 1) {
    T = 1;
  } else {
    cin >> T;
  }

  while (T--) {
    int N, M;
    if (argc > 1) {
      N = 100;
      M = 100;
    } else {
      cin >> N >> M;
    }

    vc A(N, vi(M));
    if (argc > 1) {
      for (auto &r : A) {
        for (auto &e : r) {
          e = rng() % MAXA + 1;
        }
      }
    } else {
      for (auto &r : A) {
        for (auto &e : r) {
          cin >> e;
        }
      }
    }

    int Q;
    if (argc > 1) {
      Q = 100;
    } else {
      cin >> Q;
    }

    vc<tuple<int, int, int>> queries(Q);
    if (argc > 1) {
      auto A2 = A;

      for (auto &[r, c, x] : queries) {
        do {
          r = rng() % N;
          c = rng() % M;
        } while (A2[r][c] == 1);

        x = rng() % (A2[r][c] - 1) + 1;

        A2[r][c] -= x;
      }
    } else {
      for (auto &[r, c, x] : queries) {
        cin >> r >> c >> x;
        r--, c--;
      }
    }

    auto A2 = A;

    pii deltas[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    auto is_inside = [&](int i, int j) -> bool {
      return 0 <= i and i < N and 0 <= j and j < M;
    };

    vc label(N, vi(M));
    int t = 0;
    rep(i, 0, N) {
      rep(j, 0, M) {
        label[i][j] = t;
        t++;
      }
    }

    dsu d(N * M + Q);
    rep(i, 0, N) {
      rep(j, 0, M) {
        for (auto [di, dj] : deltas) {
          int i2 = i + di, j2 = j + dj;
          if (!is_inside(i2, j2)) continue;

          if (A2[i][j] == A2[i2][j2]) {
            d.merge(label[i][j], label[i2][j2]);
          }
        }
      }
    }

    vc<pii> order;
    rep(i, 0, N) {
      rep(j, 0, M) { order.eb(i, j); }
    }
    sort(all(order), [&](pii a, pii b) -> bool {
      auto [i, j] = a;
      auto [i2, j2] = b;
      return A2[i][j] < A2[i2][j2];
    });

    vc<char> hole(N * M + Q, false);
    auto get_hole = [&](int i, int j) -> char & {
      return hole[d.leader(label[i][j])];
    };

    vc<bool> sink(N * M + Q, false);
    int count = 0;
    for (auto [i, j] : order) {
      if (sink[label[i][j]]) continue;

      get_hole(i, j) = true;
      count++;

      auto dfs = [&](auto self, int i, int j) -> void {
        if (sink[label[i][j]]) return;
        sink[label[i][j]] = true;

        for (auto [di, dj] : deltas) {
          int i2 = i + di, j2 = j + dj;
          if (!is_inside(i2, j2)) continue;
          if (A2[i2][j2] < A2[i][j]) continue;

          self(self, i2, j2);
        }
      };
      dfs(dfs, i, j);
    }

    vi ans;
    ans.pb(count);

    for (auto [i, j, x] : queries) {
      if (get_hole(i, j)) {
        get_hole(i, j) = false;
        count--;
      }

      A2[i][j] -= x;

      label[i][j] = t;
      t++;

      for (auto [di, dj] : deltas) {
        int i2 = i + di, j2 = j + dj;
        if (!is_inside(i2, j2)) continue;

        if (A2[i][j] == A2[i2][j2]) {
          if (get_hole(i2, j2)) {
            get_hole(i2, j2) = false;
            count--;
          }

          d.merge(label[i][j], label[i2][j2]);
        }
      }

      bool ok = false;
      for (auto [di, dj] : deltas) {
        int i2 = i + di, j2 = j + dj;
        if (!is_inside(i2, j2)) continue;

        ok = ok or A2[i][j] > A2[i2][j2];
      }
      if (!ok) {
        get_hole(i, j) = true;
        count++;
      }

      for (auto [di, dj] : deltas) {
        int i2 = i + di, j2 = j + dj;
        if (!is_inside(i2, j2)) continue;

        if (A2[i][j] < A2[i2][j2]) {
          if (get_hole(i2, j2)) {
            get_hole(i2, j2) = false;
            count--;
          }
        }
      }

      ans.pb(count);
    }

    if (argc > 1) {
      auto A2 = A;

      auto solve = [&]() -> int {
        vc<pii> order;
        rep(i, 0, N) {
          rep(j, 0, M) { order.eb(i, j); }
        }
        sort(all(order), [&](pii a, pii b) -> bool {
          auto [i, j] = a;
          auto [i2, j2] = b;
          return A2[i][j] < A2[i2][j2];
        });

        vc sink(N, vc<bool>(M, false));
        int rv = 0;
        for (auto [i, j] : order) {
          if (sink[i][j]) continue;

          rv++;

          auto dfs = [&](auto self, int i, int j) -> void {
            if (sink[i][j]) return;
            sink[i][j] = true;

            for (auto [di, dj] : deltas) {
              int i2 = i + di, j2 = j + dj;
              if (!is_inside(i2, j2)) continue;
              if (A2[i2][j2] < A2[i][j]) continue;

              self(self, i2, j2);
            }
          };
          dfs(dfs, i, j);
        }
        return rv;
      };

      vi brute;
      brute.pb(solve());
      for (auto [r, c, x] : queries) {
        A2[r][c] -= x;
        brute.pb(solve());
      }

      cerr << "ans:\t";
      for (auto e : ans) {
        cerr << e << ' ';
      }
      cerr << '\n';
      cerr << "brute:\t";
      for (auto e : brute) {
        cerr << e << ' ';
      }
      cerr << '\n';

      assert(ans == brute);
    } else {
      for (auto e : ans) {
        cout << e << '\n';
      }
    }
  }
}
