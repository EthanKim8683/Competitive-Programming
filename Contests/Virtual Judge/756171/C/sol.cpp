#include <bits/stdc++.h>

#include <stdexcept>

using namespace std;

using i64 = long long;

const i64 INF = 1e18;
const int L = 1e6;
const int Q = 1000;

int main() {
  cin.tie(0)->sync_with_stdio(0);

#ifdef ETHANKIM8683
  mt19937 rng(time(nullptr));

  int N = 7;

  vector<pair<int, int>> balls;
  for (int i = 0; i < N; i++) {
    int x, y;
    do {
      x = rng() % (L + 1);
      y = rng() % (L + 1);
    } while (find(balls.begin(), balls.end(), make_pair(x, y)) != balls.end());
    balls.push_back({x, y});
  }

  vector<bool> found(N, false);
  int q = 0, n = 0;
  auto query = [&](int x, int y) -> i64 {
    q++;
    if (q > Q) {
      throw runtime_error("query limit exceeded");
    }
    if (n == 8) {
      throw runtime_error("continued after finding all balls");
    }
    if (x < 0 or x > L or y < 0 or y > L) {
      throw runtime_error("query out of bounds");
    }

    pair<i64, int> ball = {INF, -1};
    for (int i = 0; i < N; i++) {
      if (found[i]) continue;
      auto [x_, y_] = balls[i];
      int dx = x_ - x, dy = y_ - y;
      ball = min(ball, {(i64) dx * dx + (i64) dy * dy, i});
    }

    auto [dist2, i] = ball;
    if (dist2 == 0) {
      n++;
      found[i] = true;
      cerr << "found ball " << i + 1 << endl;
      if (n == 8) {
        cerr << "found all balls" << endl;
      }
    }
    return dist2;
  };
#else
  int N;
  cin >> N;

  auto query = [&](int x, int y) -> i64 {
    cout << x << ' ' << y << endl;
    i64 rv;
    cin >> rv;
    return rv;
  };
#endif

  // raymarching?

  auto isqrt = [&](i64 x) -> int {
    int l = 0, r = 1e9;
    while (l < r) {
      int m = l + (r - l + 1) / 2;
      (i64) m *m <= x ? l = m : r = m - 1;
    }
    return l;
  };

  for (int i = 0; i < N; i++) {
    int x = 0, y = 0, dist = 1;
    while (true) {
      pair<int, int> dirs[] = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};
      pair<i64, int> dir = {INF, -1};
      for (int j = 0; j < 4; j++) {
        auto [dx, dy] = dirs[j];
        int x_ = x + dx * dist, y_ = y + dy * dist;
        x_ = max(x_, 0);
        x_ = min(x_, L);
        y_ = max(y_, 0);
        y_ = min(y_, L);

        i64 dist2 = query(x_, y_);
        dir = min(dir, {dist2, j});
        if (dist2 == 0) break;
      }

      auto [dist2, j] = dir;
      if (dist2 == 0) break;

      auto [dx, dy] = dirs[j];
      x += dist * dx;
      y += dist * dy;
      x = max(x, 0);
      x = min(x, L);
      y = max(y, 0);
      y = min(y, L);
      dist = isqrt(dist2);
    }
  }
}