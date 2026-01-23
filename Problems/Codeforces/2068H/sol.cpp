#include <bits/stdc++.h>

#include "ethankim8683/utils.hpp"

using namespace std;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  int A, B;
  cin >> A >> B;

  vector<int> D(N - 1);
  for (auto &e : D) cin >> e;

  auto get_distance_range = [&](vector<int> D) -> pair<i64, i64> {
    if (D.empty()) return {0, 0};
    int j = max_element(D.begin(), D.end()) - D.begin();
    i64 r1 = D[j], r2 = 0;
    for (int i = 0; i < D.size(); i++) {
      if (i == j) continue;
      r2 += D[i];
    }
    return {max(r1 - r2, 0ll), r1 + r2};
  };

  if (false) {
    viz([&]() -> void {
      set<pair<int, int>> S;
      S.emplace(0, 0);

      for (auto e : D) {
        set<pair<int, int>> S2;
        for (auto [x, y] : S) {
          for (int i = -e; i <= e; i++) {
            S2.emplace(x + i, y + e - abs(i));
            S2.emplace(x + i, y + abs(i) - e);
          }
        }

        S.clear();
        for (auto [x, y] : S2) {
          if (x < -20 or 20 <= x or y < -20 or 20 <= y) continue;
          S.emplace(x, y);
        }
      }

      ClearBackground(BLACK);
      for (auto [x, y] : S) {
        DrawRectangle(200 + x * 10, 200 + y * 10, 10, 10, RED);
      }

      auto [l, r] = get_distance_range(D);
      for (int i = -20; i < 20; i++) {
        for (int j = -20; j < 20; j++) {
          int d = abs(i) + abs(j);
          if (l <= d and d <= r and d % 2 == r % 2) {
            DrawRectangleLines(200 + i * 10, 200 + j * 10, 10, 10, GREEN);
          }
        }
      }
    });
  }

  auto [l, r] = get_distance_range(D);
  int d = A + B;
  if (!(l <= d and d <= r and d % 2 == r % 2)) {
    cout << "NO\n";
    exit(0);
  }

  if (false) {
    viz([&]() -> void {
      auto [l, r] = get_distance_range({D.begin(), D.end() - 1});
      for (int i = -20; i < 20; i++) {
        for (int j = -20; j < 20; j++) {
          int d1 = abs(i) + abs(j);
          if (l <= d1 and d1 <= r and d1 % 2 == r % 2) {
            DrawRectangle(200 + i * 10, 200 + j * 10, 10, 10, RED);
          }

          int d2 = abs(i - A) + abs(j - B);
          if (d2 == D.back()) {
            DrawRectangleLines(200 + i * 10, 200 + j * 10, 10, 10, YELLOW);
          }
        }
      }

      DrawRectangle(200 + A * 10, 200 + B * 10, 10, 10, YELLOW);
    });
  }

  pair<i64, i64> nil = {INF, INF};
  auto find_common_point = [&](pair<i64, i64> src, int d, pair<i64, i64> dest,
                               pair<i64, i64> range) -> pair<i64, i64> {
    auto solve_line = [&](pair<i64, i64> p1,
                          pair<i64, i64> p2) -> pair<i64, i64> {
      auto solve_simple_line = [&](pair<i64, i64> p1,
                                   pair<i64, i64> p2) -> pair<i64, i64> {
        auto [x1, y1] = p1;
        auto [x2, y2] = p2;
        auto [l1, r1] = range;

        auto get_y = [&](i64 x) -> i64 {
          assert((y2 - y1) % (x2 - x1) == 0);
          return y1 + (y2 - y1) / (x2 - x1) * (x - x1);
        };
        auto get_distance = [&](i64 x) -> i64 {
          i64 y = get_y(x);
          auto [x2, y2] = dest;
          return abs(x - x2) + abs(y - y2);
        };

        i64 l2 = get_distance(x1), r2 = get_distance(x2);
        if (l2 > r2) {
          swap(l2, r2);
          swap(x1, x2);
          swap(y1, y2);
        }

        assert(l2 % 2 == r2 % 2);
        if (r2 % 2 != r1 % 2) return nil;

        if (max(l2, l1) > min(r2, r1)) return nil;

        i64 x3, y3;
        if (l2 == r2) {
          x3 = x1;
          y3 = y1;
        } else {
          assert((r2 - l2) % (x2 - x1) == 0);
          x3 = x1 + (max(l2, l1) - l2) / ((r2 - l2) / (x2 - x1));
          y3 = get_y(x3);
        }

        auto [x4, y4] = src;
        assert(abs(x3 - x4) + abs(y3 - y4) == d);

        auto [x5, y5] = dest;
        i64 d2 = abs(x3 - x5) + abs(y3 - y5);
        assert(l1 <= d2 and d2 <= r1);

        return {x3, y3};
      };

      auto [x1, y1] = p1;
      auto [x2, y2] = p2;
      auto [x3, y3] = dest;

      auto get_y = [&](i64 x) -> i64 {
        assert((y2 - y1) % (x2 - x1) == 0);
        return y1 + (y2 - y1) / (x2 - x1) * (x - x1);
      };
      auto get_x = [&](i64 y) -> i64 {
        assert((x2 - x1) % (y2 - y1) == 0);
        return x1 + (x2 - x1) / (y2 - y1) * (y - y1);
      };

      vector<i64> X;
      X.push_back(x1);
      X.push_back(x2);
      if (min(x1, x2) <= x3 and x3 <= max(x1, x2)) {
        X.push_back(x3);
      }
      if (min(y1, y2) <= y3 and y3 <= max(y1, y2)) {
        X.push_back(get_x(y3));
      }
      sort(X.begin(), X.end());
      X.erase(unique(X.begin(), X.end()), X.end());
      for (int i = 0; i + 1 < X.size(); i++) {
        auto p =
            solve_simple_line({X[i], get_y(X[i])}, {X[i + 1], get_y(X[i + 1])});
        if (p != nil) return p;
      }
      return nil;
    };

    auto [x, y] = src;

    if (d == 0) {
      auto [x2, y2] = dest;
      auto [l, r] = range;

      int d2 = abs(x - x2) + abs(y - y2);
      if (l <= d2 and d2 <= r and d2 % 2 == r % 2) {
        return src;
      }
      return nil;
    }

    vector<pair<i64, i64>> P;
    P.emplace_back(x, y - d);
    P.emplace_back(x + d, y);
    P.emplace_back(x, y + d);
    P.emplace_back(x - d, y);
    for (int i = 0; i < 4; i++) {
      auto p = solve_line(P[i], P[(i + 1) % 4]);
      if (p != nil) return p;
    }
    return nil;
  };
  pair<i64, i64> pos = {A, B};
  vector<pair<i64, i64>> ans;
  ans.push_back(pos);
  for (int i = N - 2; i >= 0; i--) {
    auto range = get_distance_range({D.begin(), D.begin() + i});
    pos = find_common_point(pos, D[i], {0, 0}, range);
    assert(pos != nil);

    ans.push_back(pos);
  }
  reverse(ans.begin(), ans.end());

  cout << "YES\n";
  for (auto [x, y] : ans) {
    cout << x << ' ' << y << '\n';
  }
}
