#include <bits/stdc++.h>

using namespace std;

using i64 = long long;
using f64 = long double;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<pair<int, int>> points(N);
  for (auto &[x, y] : points) {
    cin >> x >> y;
  }

  auto cross = [&](pair<int, int> A, pair<int, int> B) -> i64 {
    auto [x1, y1] = A;
    auto [x2, y2] = B;
    return (i64) x1 * y2 - (i64) y1 * x2;
  };

  auto delta = [&](pair<int, int> A, pair<int, int> B) -> pair<i64, i64> {
    auto [x1, y1] = A;
    auto [x2, y2] = B;
    return {x2 - x1, y2 - y1};
  };

  vector<pair<int, int>> stack, left(N), right(N);
  for (int i = 0; i < N; i++) {
    while (stack.size() >= 2 and
           cross(delta(stack.end()[-1], points[i]),
                 delta(stack.end()[-1], stack.end()[-2])) <= 0) {
      stack.pop_back();
    }
    if (i > 0) {
      left[i] = stack.back();
    }
    stack.push_back(points[i]);
  }
  stack.clear();
  for (int i = N - 1; i >= 0; i--) {
    while (stack.size() >= 2 and
           cross(delta(stack.end()[-1], points[i]),
                 delta(stack.end()[-1], stack.end()[-2])) >= 0) {
      stack.pop_back();
    }
    if (i < N - 1) {
      right[i] = stack.back();
    }
    stack.push_back(points[i]);
  }

  f64 ans = 0;
  for (int i = 1; i < N - 1; i++) {
    auto [x1, y1] = left[i];
    auto [x2, y2] = points[i];
    auto [x3, y3] = right[i];

    f64 x_1 = (f64) y2 / (y2 - y1) * (x1 - x2) + x2;
    f64 x_3 = (f64) y2 / (y2 - y3) * (x3 - x2) + x2;

    ans = max(ans, (f64) y2 * (x_3 - x_1) / 2);
  }
  cout << setprecision(14) << fixed << ans;
}