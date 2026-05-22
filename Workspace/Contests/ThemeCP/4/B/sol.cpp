#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, Q;
    cin >> N >> Q;

    vector M(N, vector<int>(N));
    for (auto &r : M) {
      for (auto &e : r) {
        cin >> e;
      }
    }

    vector base(N + 1, vector<i64>(N + 1, 0)),
        slope_h(N + 1, vector<i64>(N + 1, 0)),
        slope_v(N + 1, vector<i64>(N + 1, 0));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        base[i + 1][j + 1] = M[i][j];
        slope_h[i + 1][j + 1] = (i64) (j + 1) * M[i][j];
        slope_v[i + 1][j + 1] = (i64) i * M[i][j];
      }
    }
    auto make = [&](vector<vector<i64>> &ps) -> void {
      for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
          ps[i][j] += ps[i - 1][j] + ps[i][j - 1] - ps[i - 1][j - 1];
        }
      }
    };
    auto query = [&](vector<vector<i64>> &ps, int x1, int y1, int x2,
                     int y2) -> i64 {
      return ps[x2][y2] - ps[x1][y2] - ps[x2][y1] + ps[x1][y1];
    };
    make(base);
    make(slope_h);
    make(slope_v);

    while (Q--) {
      int x1, x2, y1, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      x1--, y1--;

      cout << query(slope_h, x1, y1, x2, y2) -
                  y1 * query(base, x1, y1, x2, y2) +
                  (y2 - y1) * (query(slope_v, x1, y1, x2, y2) -
                               x1 * query(base, x1, y1, x2, y2))
           << ' ';
    }
    cout << '\n';
  }
}
