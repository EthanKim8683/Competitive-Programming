#include <bits/stdc++.h>

using namespace std;

using f64 = long double;

const f64 SCALE = 1e3;
const f64 EPSILON = 1e-3;
const f64 INF = 1e300;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<pair<f64, f64>> holds(N);
  for (auto &[x, y] : holds) {
    cin >> x >> y;
  }
  holds.push_back({-0.2, 0});
  holds.push_back({0, 0});
  holds.push_back({0.2, 0});

  for (auto &[x, y] : holds) {
    x *= SCALE;
    y *= SCALE;
  }

  auto delta = [&](pair<f64, f64> A, pair<f64, f64> B) -> pair<f64, f64> {
    auto [xA, yA] = A;
    auto [xB, yB] = B;
    return {xB - xA, yB - yA};
  };

  auto distance = [&](pair<f64, f64> A, pair<f64, f64> B) -> f64 {
    auto [dx, dy] = delta(A, B);
    return sqrt(dx * dx + dy * dy);
  };

  auto intersect = [&](pair<f64, f64> A,
                       pair<f64, f64> B) -> vector<pair<f64, f64>> {
    auto [xA, yA] = A;
    auto [dx, dy] = delta(A, B);
    f64 mx = xA + dx / 2, my = yA + dy / 2;
    f64 p2 = SCALE * SCALE - (dx * dx + dy * dy) / 4;
    if (p2 < 0) return {};
    if (p2 == 0) return {{mx, my}};
    f64 p = sqrt(p2);
    f64 s = p / distance(A, B);
    f64 px = dx * s, py = dy * s;
    return {{mx + py, my - px}, {mx - py, my + px}};
  };

  auto coverage = [&](pair<f64, f64> A, pair<f64, f64> B,
                      pair<f64, f64> C) -> pair<f64, f64> {
    // (x-Ax)/a = (y-Ay)/b
    // b(x-Ax) = a(y-Ay)
    // bx - ay = bAx - aAy
    //
    // let ax + by = c, bx - ay = d
    // (b^2/a)x - by = bd/a
    // (a+b^2/a)x = c + bd/a
    // (a^2+b^2)x = ac + bd
    // x = (ac+bd)/(a^2+b^2)
    // -ax + (a^2/b)y = -ad/b
    // (b+a^2/b)y = c - ad/b
    // (a^2+b^2)y = bc - ad
    // y = (bc-ad)/(a^2+b^2)

    auto coefficients = [&](f64 dx, f64 dy, f64 x0,
                            f64 y0) -> tuple<f64, f64, f64> {
      return {dy, -dx, dy * x0 - dx * y0};
    };

    f64 mx, my;
    {
      auto [dx, dy] = delta(A, B);
      auto [Ax, Ay] = A;
      auto [Cx, Cy] = C;
      auto [a, b, c] = coefficients(dx, dy, Ax, Ay);
      auto [_a, _b, d] = coefficients(dy, -dx, Cx, Cy);
      mx = (a * c + b * d) / (a * a + b * b);
      my = (b * c - a * d) / (a * a + b * b);
    }
    f64 r;
    {
      auto [dx, dy] = delta(C, {mx, my});
      f64 r2 = SCALE * SCALE - (dx * dx + dy * dy);
      if (r2 < 0) return {-1, -1};
      r = sqrt(r2);
    }
    f64 t, dt;
    {
      auto [Ax, Ay] = A;
      auto [dx, dy] = delta(A, B);
      t = dx != 0 ? SCALE * (mx - Ax) / dx : SCALE * (my - Ay) / dy;
      dt = SCALE * r / distance(A, B);
    }
    return {max(t - dt, 0.L), min(t + dt, SCALE)};
  };

  auto reachable = [&](pair<f64, f64> A, pair<f64, f64> B) -> bool {
    if (A == B) return true;
    map<f64, int> delta;
    delta[0] = 0;
    for (int i = 0; i < holds.size(); i++) {
      auto [l, r] = coverage(A, B, holds[i]);
      delta[l - EPSILON] += 1;
      delta[r + EPSILON] -= 1;
    }
    bool ok = true;
    int sum = 0;
    for (auto [t, d] : delta) {
      sum += d;
      if (0 <= t and t < SCALE) {
        ok = ok and sum >= 3;
      }
    }
    return ok;
  };

  auto nearest = [&](pair<f64, f64> A, pair<f64, f64> B) -> pair<f64, f64> {
    auto [dx, dy] = delta(A, B);
    f64 d = distance(A, B);
    if (d < SCALE) return B;
    f64 s = SCALE / d;
    f64 nx = dx * s, ny = dy * s;
    auto [Ax, Ay] = A;
    return {Ax + nx, Ay + ny};
  };

  set<pair<f64, f64>> points;
  for (int i = 0; i < holds.size(); i++) {
    for (int j = i + 1; j < holds.size(); j++) {
      auto [x1, y1] = holds[i];
      auto [x2, y2] = holds[j];
      for (auto e : intersect(holds[i], holds[j])) {
        points.insert(e);
      }
    }
  }
  points.insert({0, 0});

  map<pair<f64, f64>, f64> dist;
  priority_queue<pair<f64, pair<f64, f64>>> pq;
  auto push = [&](pair<f64, f64> a, f64 d) -> void {
    if (dist.find(a) != dist.end() and d >= dist[a]) return;
    dist[a] = d;
    pq.push({-d, a});
  };
  push({0, 0}, 0);
  while (pq.size() > 0) {
    auto [d, a] = pq.top();
    pq.pop();
    if ((d = -d) != dist[a]) continue;
    for (auto b : points) {
      if (!reachable(a, b)) continue;
      push(b, d + distance(a, b));
    }
  }
  f64 ans = INF;
  for (auto e : points) {
    if (dist.find(e) == dist.end()) continue;
    auto n = nearest(holds[N - 1], e);
    if (!reachable(e, n)) continue;
    ans = min(ans, dist[e] + distance(e, n));
  }
  if (ans == INF) {
    cout << -1;
  } else {
    ans /= SCALE;
    cout << setprecision(14) << fixed << ans;
  }
}