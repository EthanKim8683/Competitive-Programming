#include <bits/stdc++.h>

// #include "ethankim8683/viz"

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // int N = 3, M = 3;

  // vector<int> P(N * M);
  // iota(P.begin(), P.end(), 0);
  // do {
  //   vector colored(N, vector<bool>(M, false));
  //   vector penalties(N, vector<int>(M, 0));
  //   for (auto e : P) {
  //     int x1 = e / M, y1 = e % M;
  //     pair<int, int> furthest_dist = {0, 0};
  //     vector<pair<int, int>> furthest;
  //     for (int x2 = 0; x2 < N; x2++) {
  //       for (int y2 = 0; y2 < M; y2++) {
  //         if (!colored[x2][y2]) continue;

  //         pair<int, int> dist = {max(abs(x1 - x2), abs(y1 - y2)),
  //                                abs(x1 - x2) + abs(y1 - y2)};
  //         if (dist > furthest_dist) {
  //           furthest_dist = dist;
  //           furthest.clear();
  //           furthest.push_back({x2, y2});
  //         }
  //       }
  //     }
  //     for (auto [x2, y2] : furthest) {
  //       penalties[x2][y2]++;
  //     }
  //     colored[x1][y1] = true;
  //   }

  //   bool ok = true;
  //   for (auto r : penalties) {
  //     for (auto e : r) {
  //       ok = ok and e <= 3;
  //     }
  //   }
  //   if (!ok) continue;

  //   vector indices(N, vector<int>(M, -1));
  //   penalties = vector(N, vector<int>(M, 0));
  //   for (int i = 0; i < N * M; i++) {
  //     int x1 = P[i] / M, y1 = P[i] % M, furthest_dist = 0;
  //     vector<pair<int, int>> furthest;
  //     for (int x2 = 0; x2 < N; x2++) {
  //       for (int y2 = 0; y2 < M; y2++) {
  //         if (indices[x2][y2] == -1) continue;

  //         int dist = abs(x1 - x2) + abs(y1 - y2);
  //         if (dist > furthest_dist) {
  //           furthest_dist = dist;
  //           furthest.clear();
  //           furthest.push_back({x2, y2});
  //         }
  //       }
  //     }
  //     for (auto [x2, y2] : furthest) {
  //       penalties[x2][y2]++;
  //     }
  //     indices[x1][y1] = i;

  //     viz([&]() -> void {
  //       ClearBackground(WHITE);
  //       int K = 20;
  //       for (int x = 0; x < N; x++) {
  //         for (int y = 0; y < M; y++) {
  //           DrawRectangleLines(x * K, y * K, K, K, BLACK);
  //           if (indices[x][y] != -1) {
  //             DrawText(to_string(indices[x][y]).c_str(), x * K, y * K, 10,
  //                      BLACK);
  //           }
  //           DrawText(to_string(penalties[x][y]).c_str(), x * K, y * K + 10,
  //           10,
  //                    BLACK);
  //         }
  //       }
  //       for (auto [x, y] : furthest) {
  //         DrawRectangleLines(x * K, y * K, K, K, RED);
  //       }
  //       DrawRectangleLines(x1 * K, y1 * K, K, K, GREEN);
  //     });
  //   }

  //   break;
  // } while (next_permutation(P.begin(), P.end()));

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vector<pair<int, int>> ans;
    ans.push_back({0, 0});

    int w = 1, h = 1;

    auto grow_w = [&]() -> void {
      if (w >= N) return;
      int x_l = -(w + 1) / 2, x_r = -x_l;
      for (int i = 0; i < h; i++) {
        int y_l = (i + 1) / 2 * (i % 2 == 0 ? 1 : -1), y_r = -y_l;
        ans.push_back({x_l, y_l});
        ans.push_back({x_r, y_r});
      }
      w += 2;
    };
    auto grow_h = [&]() -> void {
      if (h >= M) return;
      int y_t = -(h + 1) / 2, y_b = -y_t;
      for (int i = 0; i < w; i++) {
        int x_t = (i + 1) / 2 * (i % 2 == 0 ? 1 : -1), x_b = -x_t;
        ans.push_back({x_t, y_t});
        ans.push_back({x_b, y_b});
      }
      h += 2;
    };
    for (int i = 0; w < N or h < M; i++) {
      i % 2 == 0 ? grow_w() : grow_h();
    }
    for (auto &[x, y] : ans) {
      x += (N - 1) / 2 + 1;
      y += (M - 1) / 2 + 1;
    }

    for (auto [x, y] : ans) {
      cout << x << ' ' << y << '\n';
    }
    cout << '\n';

    // vector colored(N, vector<bool>(M, false));
    // vector penalties(N, vector<int>(M, 0));
    // for (auto [x1, y1] : ans) {
    //   pair<int, int> furthest_dist = {0, 0};
    //   vector<pair<int, int>> furthest;
    //   for (int x2 = 0; x2 < N; x2++) {
    //     for (int y2 = 0; y2 < M; y2++) {
    //       if (!colored[x2][y2]) continue;

    //       pair<int, int> dist = {max(abs(x1 - x2), abs(y1 - y2)),
    //                              abs(x1 - x2) + abs(y1 - y2)};
    //       if (dist > furthest_dist) {
    //         furthest_dist = dist;
    //         furthest.clear();
    //         furthest.push_back({x2, y2});
    //       }
    //     }
    //   }
    //   for (auto [x2, y2] : furthest) {
    //     penalties[x2][y2]++;
    //   }
    //   colored[x1][y1] = true;
    // }

    // bool ok = true;
    // for (auto r : penalties) {
    //   for (auto e : r) {
    //     ok = ok and e <= 3;
    //   }
    // }
    // cerr << (ok ? "PASS" : "FAIL") << '\n';

    // vector index(N, vector<int>(M, -1));
    // for (int i = 0; i < ans.size(); i++) {
    //   auto [x, y] = ans[i];
    //   index[x][y] = i;
    //   viz([&]() -> void {
    //     int K = 40;

    //     ClearBackground(WHITE);
    //     for (int j = 0; j < N; j++) {
    //       for (int k = 0; k < M; k++) {
    //         DrawRectangleLines(j * K, k * K, K, K, BLACK);
    //         if (index[j][k] != -1) {
    //           DrawText(to_string(index[j][k]).c_str(), j * K, k * K, 20,
    //           BLACK);
    //         }
    //       }
    //     }
    //     DrawRectangleLines(x * K, y * K, K, K, GREEN);
    //   });
    // }
  }
}