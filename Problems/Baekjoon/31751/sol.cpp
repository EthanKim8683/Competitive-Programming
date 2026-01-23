#ifndef L
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
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

const int MAXP = 1e9;
const double INF = 1. / 0;

template <class T>
int sgn(T x) {
  return (x > 0) - (x < 0);
}
template <class T>
struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
  P operator+(P p) const { return P(x + p.x, y + p.y); }
  P operator-(P p) const { return P(x - p.x, y - p.y); }
  P operator*(T d) const { return P(x * d, y * d); }
  P operator/(T d) const { return P(x / d, y / d); }
  T dot(P p) const { return x * p.x + y * p.y; }
  T cross(P p) const { return x * p.y - y * p.x; }
  T dist2() const { return x * x + y * y; }
  double dist() const { return sqrt((double) dist2()); }
  T cross(P a, P b) const { return (a - *this).cross(b - *this); }
  bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
  bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
  double angle() const { return atan2(y, x); }
  P unit() const { return *this / dist(); }
  P perp() const { return P(-y, x); }
  P normal() const { return perp().unit(); }
  P rotate(double a) const {
    return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
  }
  friend ostream &operator<<(ostream &os, P p) {
    return os << "(" << p.x << "," << p.y << ")";
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main(signed argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 3:54
  // thinking done: 3:58
  // target impl time: 30 min
  // initial impl time: 1 hr 10 min

  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[1]));
  }

  int N;
  if (argc > 1) {
    N = 1e6;
  } else {
    cin >> N;
  }

  vc<tuple<int, int, int, int>> meteors(N);
  for (auto &[X, Y, Vx, Vy] : meteors) {
    if (argc > 1) {
      X = rng() % (2 * MAXP + 1) - MAXP;
      Y = rng() % (2 * MAXP + 1) - MAXP;
      Vx = rng() % (2 * MAXP + 1) - MAXP;
      Vy = rng() % (2 * MAXP + 1) - MAXP;
    } else {
      cin >> X >> Y >> Vx >> Vy;
    }
  }

  auto build_convex_hull = [&](vc<Point<int>> lines) -> vc<Point<int>> {
    sort(all(lines));
    vc<Point<int>> slopes;
    rep(i, 0, sz(lines)) {
      if (i == 0 or lines[i].x != lines[i - 1].x) {
        slopes.pb(lines[i]);
      }
    }
    reverse(all(slopes));
    vc<Point<int>> stack;
    for (auto e : slopes) {
      // m1 * x + b1 = m2 * x + b2
      // x = (b2 - b1) / (m1 - m2)
      // (b2 - b1) / (m1 - m2) <= (b3 - b1) / (m1 - m3)
      // (m1 - m3) * (b2 - b1) <= (m1 - m2) * (b3 - b1)
      // (m1 - m3) * (b2 - b1) - (m1 - m2) * (b3 - b1) <= 0
      // (m3 - m1) * (b2 - b1) - (m2 - m1) * (b3 - b1) >= 0
      // cross(v3 - v1, v2 - v1) >= 0
      // v1 = e
      // v2 = stack.back()
      // v3 = stack.end()[-2]
      while (sz(stack) >= 2 and
             (stack.end()[-2] - e).cross(stack.back() - e) >= 0) {
        stack.pop_back();
      }
      stack.push_back(e);
    }
    return stack;
  };

  auto find_intersection = [&](Point<int> v1, Point<int> v2) -> double {
    auto [m1, b1] = v1;
    auto [m2, b2] = v2;
    return (double) (b2 - b1) / (m1 - m2);
  };

  auto find_minimizer = [&](Point<int> v1, Point<int> v2) -> double {
    // (m1 * x + b1) * (m2 * x + b2)
    // m1 * m2 * x ^ 2 + (m1 * b2 + m2 * b1) * x + b1 * b2
    // 2 * m1 * m2 * x + m1 * b2 + m2 * b1 = 0
    // x = -(m1 * b2 + m2 * b1) / (2 * m1 * m2)
    auto [m1, b1] = v1;
    auto [m2, b2] = v2;
    return (double) -(m1 * b2 + m2 * b1) / (2 * m1 * m2);
  };

  auto with_lower_bounds = [&](vc<Point<int>> hull) -> map<double, Point<int>> {
    map<double, Point<int>> rv;
    rv[-INF] = hull[0];
    rep(i, 1, sz(hull)) {
      rv[find_intersection(hull[i - 1], hull[i])] = hull[i];
    }
    return rv;
  };

  auto add_hulls = [&](vc<Point<int>> hull1,
                       vc<Point<int>> hull2) -> vc<Point<int>> {
    if (hull1.empty()) return hull2;
    if (hull2.empty()) return hull1;
    vc<Point<int>> rv;
    rv.pb(hull1[0] + hull2[0]);
    for (int i = 1, j = 1; i < sz(hull1) or j < sz(hull2);) {
      if (i < sz(hull1) and j < sz(hull2)) {
        if (find_intersection(hull1[i - 1], hull1[i]) <
            find_intersection(hull2[j - 1], hull2[j])) {
          rv.pb(hull1[i] + hull2[j - 1]);
          i++;
        } else {
          rv.pb(hull1[i - 1] + hull2[j]);
          j++;
        }
      } else if (i < sz(hull1)) {
        rv.pb(hull1[i] + hull2[j - 1]);
        i++;
      } else if (j < sz(hull2)) {
        rv.pb(hull1[i - 1] + hull2[j]);
        j++;
      }
    }
    return rv;
  };

  auto hull1 = [&]() -> vc<Point<int>> {
    vc<Point<int>> lines1, lines2;
    for (auto [X, Y, Vx, Vy] : meteors) {
      lines1.eb(Vx, X);
      lines2.eb(-Vx, -X);
    }
    vc<Point<int>> hull1 = build_convex_hull(lines1),
                   hull2 = build_convex_hull(lines2);
    for (auto &e : hull1) {
      e = e * -1;
    }
    for (auto &e : hull2) {
      e = e * -1;
    }
    return add_hulls(hull1, hull2);
  }();

  auto hull2 = [&]() -> vc<Point<int>> {
    vc<Point<int>> lines1, lines2;
    for (auto [X, Y, Vx, Vy] : meteors) {
      lines1.eb(Vy, Y);
      lines2.eb(-Vy, -Y);
    }
    vc<Point<int>> hull1 = build_convex_hull(lines1),
                   hull2 = build_convex_hull(lines2);
    for (auto &e : hull1) {
      e = e * -1;
    }
    for (auto &e : hull2) {
      e = e * -1;
    }
    return add_hulls(hull1, hull2);
  }();

  auto f1 = with_lower_bounds(hull1), f2 = with_lower_bounds(hull2);

  auto side_at = [&](map<double, Point<int>> &f, double x) -> double {
    auto [m, b] = prev(f.upper_bound(x))->second;
    return m * x + b;
  };

  auto area_at = [&](double x) -> double {
    return side_at(f1, x) * side_at(f2, x);
  };

  set<double> lower_bounds;
  for (auto [l, line] : f1) {
    lower_bounds.insert(l);
  }
  for (auto [l, line] : f2) {
    lower_bounds.insert(l);
  }
  set<double> critical_points;
  critical_points.insert(0);
  for (auto e : lower_bounds) {
    if (e >= 0) {
      critical_points.insert(e);
    }
    auto line1 = prev(f1.upper_bound(e))->second,
         line2 = prev(f2.upper_bound(e))->second;
    double t = find_minimizer(line1, line2);
    if (t >= 0) {
      critical_points.insert(t);
    }
  }
  double ans = INF;
  for (auto e : critical_points) {
    chmin(ans, area_at(e));
  }
  cout << setprecision(13) << fixed << ans << '\n';
}
