#include <bits/stdc++.h>

#include "atcoder/dsu"
#include "atcoder/modint"
#include "ethankim8683/utils"

using namespace std;
using namespace atcoder;
using mint = modint1000000007;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, M, K;
    cin >> N >> M >> K;

    vector<pair<int, int>> P(K + 1);
    for (auto &[x, y] : P) {
      cin >> x >> y;
      x--, y--;
    }

    // viz([&]() -> void {
    //   vector index(N, vector<int>(M, -1));
    //   for (int i = 0; i < K + 1; i++) {
    //     auto [x, y] = P[i];
    //     index[x][y] = i;
    //   }

    //   int K = 20;

    //   ClearBackground(WHITE);
    //   for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < M; j++) {
    //       DrawRectangleLines(i * K, j * K, K, K, BLACK);
    //       if (index[i][j] != -1) {
    //         DrawText(to_string(index[i][j]).c_str(), i * K, j * K, 12,
    //         BLACK);
    //       }
    //     }
    //   }
    //   for (int i = 0; i + 1 < K + 1; i++) {
    //     auto [x1, y1] = P[i];
    //     auto [x2, y2] = P[i + 1];
    //     if (abs(x1 - x2) == 1 and abs(y1 - y2) == 1) {
    //       DrawLine(x1 * K + K / 2, y2 * K + K / 2, x2 * K + K / 2,
    //                y1 * K + K / 2, BLACK);
    //     }
    //   }
    // });

    auto encode = [&](int x, int y) -> int { return x * M + y; };

    bool ok = true;
    vector<int> blocks(N * M, 0), edges(N * M, 0);
    dsu d(N * M);
    for (int i = 0; i + 1 < K + 1; i++) {
      auto [x1, y1] = P[i];
      auto [x2, y2] = P[i + 1];
      if (abs(x1 - x2) == 1 and abs(y1 - y2) == 1) {
        d.merge(encode(x1, y2), encode(x2, y1));
        edges[encode(x1, y2)]++;
      } else if ((abs(x1 - x2) == 2 and abs(y1 - y2) == 0) or
                 (abs(x1 - x2) == 0 and abs(y1 - y2) == 2)) {
        blocks[encode((x1 + x2) / 2, (y1 + y2) / 2)]++;
      } else {
        ok = false;
      }
    }
    if (!ok) {
      cout << 0 << '\n';
      continue;
    }

    for (int i = 0; i < N * M; i++) {
      int j = d.leader(i);
      if (i == j) continue;

      blocks[j] += blocks[i];
      edges[j] += edges[i];
    }

    mint ans = 1;
    for (int i = 0; i < N * M; i++) {
      if (d.size(i) == 1) continue;
      if (i != d.leader(i)) continue;

      if (blocks[i] == 1) {
        continue;
      } else if (blocks[i] > 1) {
        ans = 0;
      }

      if (d.size(i) == edges[i] + 1) {
        ans *= d.size(i);
      } else if (d.size(i) == edges[i]) {
        ans *= 2;
      } else {
        ans = 0;
      }
    }
    cout << ans.val() << '\n';
  }
}