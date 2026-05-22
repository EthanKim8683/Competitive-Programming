#include <bits/stdc++.h>

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vector<string> grid(N);
    for (auto &r : grid) cin >> r;

    vector seen(N, vector<bool>(M, false));
    auto dfs = [&](auto self, int i, int j) -> array<int, 5> {
      seen[i][j] = true;
      array<int, 5> rv = {i, -i, j, -j, 1};
      for (auto [di, dj] :
           (pair<int, int>[]) {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
        int i_ = i + di, j_ = j + dj;
        if (i_ < 0 or i_ >= N or j_ < 0 or j_ >= M or grid[i_][j_] != '#' or
            seen[i_][j_])
          continue;
        auto rv_ = self(self, i_, j_);
        for (int k = 0; k < 4; k++) {
          rv[k] = min(rv[k], rv_[k]);
        }
        rv[4] += rv_[4];
      }
      return rv;
    };
    vector ps(4, vector(N + 1, vector<int>(M + 1, 0)));
    int total = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (grid[i][j] != '#' or seen[i][j]) continue;
        auto [i_min, i_max, j_min, j_max, size] = dfs(dfs, i, j);
        i_max = -i_max;
        j_max = -j_max;
        ps[0][i_max + 1][j_max + 1] += size;
        ps[1][i_max + 1][j_min + 1] += size;
        ps[2][i_min + 1][j_max + 1] += size;
        ps[3][i_min + 1][j_min + 1] += size;
        total += size;
      }
    }
    for (int i = 0; i < 4; i++) {
      for (int j = 1; j <= N; j++) {
        for (int k = 1; k <= M; k++) {
          ps[i][j][k] +=
              ps[i][j - 1][k] + ps[i][j][k - 1] - ps[i][j - 1][k - 1];
        }
      }
    }
    auto query = [&](int i, int j1, int j2, int k1, int k2) -> int {
      if (j2 <= j1 or k2 <= k1) return 0;
      return ps[i][j2][k2] - ps[i][j1][k2] - ps[i][j2][k1] + ps[i][j1][k1];
    };

    vector ps2(N + 1, vector<int>(M + 1, 0));
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= M; j++) {
        ps2[i][j] = ps2[i - 1][j] + ps2[i][j - 1] - ps2[i - 1][j - 1] +
                    (grid[i - 1][j - 1] == '#');
      }
    }
    auto query2 = [&](int i1, int i2, int j1, int j2) -> int {
      return ps2[i2][j2] - ps2[i1][j2] - ps2[i2][j1] + ps2[i1][j1];
    };

    int ans = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        int size = total - query(0, 0, i - 1, 0, j - 1) -
                   query(1, 0, i - 1, j + 2, M) - query(2, i + 2, N, 0, j - 1) -
                   query(3, i + 2, N, j + 2, M);
        size += N + M - 1 -
                (query2(i, i + 1, 0, M) + query2(0, N, j, j + 1) -
                 (grid[i][j] == '#'));
        ans = max(ans, size);
      }
    }
    cout << ans << '\n';
  }
}
