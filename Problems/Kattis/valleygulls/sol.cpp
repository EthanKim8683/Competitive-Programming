#pragma GCC optimize("Ofast,unroll-loops")
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
typedef pair<double, double> pdd;
typedef vc<int> vi;

const double INF = 1. / 0;
const double EPSILON = 1e-3;

struct Range {
  vc<pdd> points;
  double y, r;
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 2:29
  // thinking done: 3:08
  // target impl time: 1 hr
  // initial impl done:

  // xl = 18
  // yt = -2
  // xr = 34.5
  // yb = -20

  double area1 = (double) 6 * 3 / 2,
         area2 = (double) (34.5 - 16) * ((-2) - (-20)) / 2;

  double time1 = area1 / ((10 - 0) * 0.2), time2 = area2 / ((40 - 10) * 0.2);

  cerr << area1 << ": " << time1 << '\n';
  cerr << area2 << ": " << time2 << '\n';

  int P;
  double R;
  int M;
  cin >> P >> R >> M;

  vc<pdd> points(P);
  for (auto &[x, y] : points) {
    cin >> x >> y;
  }

  vi N(M);
  for (auto &e : N) cin >> e;

  auto get_y = [&](vc<pdd> points, double x) -> double {
    rep(i, 0, sz(points) - 1) {
      auto [x1, y1] = points[i];
      auto [x2, y2] = points[i + 1];
      if (x1 <= x and x <= x2) {
        return (x - x1) / (x2 - x1) * (y2 - y1) + y1;
      }
    }
    assert(false);
  };

  auto get_ymin = [&](vc<pdd> points) -> double {
    double ymin = INF;
    rep(i, 1, sz(points) - 1) { chmax(ymin, points[i].sd); }
    return ymin;
  };

  auto get_ymax = [&](vc<pdd> points) -> double {
    return min(points[0].sd, points.back().sd);
  };

  auto get_clipped_area = [&](vc<pdd> points, double yclip) -> double {
    assert(get_ymin(points) <= yclip and yclip <= get_ymax(points));
    double rv = 0;
    rep(i, 0, sz(points) - 1) {
      auto [x1, y1] = points[i];
      auto [x2, y2] = points[i + 1];
      double xl = min(x1, x2), xr = max(x1, x2), yb = min(y1, y2),
             yt = max(y1, y2);
      if (yt > yclip) {
        rv += (yclip - yb) / (yt - yb) * (xr - xl) * (yclip - yb) / 2;
      } else {
        rv += (xr - xl) * (yt - yb) / 2;
        rv += (xr - xl) * (yclip - yt);
      }
    }
    return rv;
  };

  auto get_dt = [&](vc<pdd> points, double y, double r, double dy) -> double {
    return (get_clipped_area(points, y + dy) - get_clipped_area(points, y)) / r;
  };

  auto get_dy = [&](vc<pdd> points, double y, double r, double dt) -> double {
    double yl = max(get_ymin(points), y), yr = get_ymax(points);
    rep(i, 0, 64) {
      double ym = (yl + yr) / 2;
      get_dt(points, y, r, ym - y) <= dt ? yl = ym : yr = ym;
    }
    return yl;
  };

  vc<Range> ranges;
  // get ranges

  auto is_approx = [&](double a, double b) -> bool {
    return abs(a - b) < EPSILON;
  };

  auto is_full = [&](Range range) -> bool {
    return is_approx(get_ymax(range.points), range.y);
  };

  auto nudge = [&](int i) -> void {
    auto range = ranges[i];
    if (!is_full(range)) return;
    if (range.points[0].fs < range.points.back().sd) {
      if (is_full(ranges[i - 1])) {
      }
    } else {
    }
  };

  double t = 0;
  while (true) {
    double dtmin = INF;
    for (auto e : ranges) {
      double dt = get_dt(e.points, e.y, e.r, get_ymax(e.points) - e.y);
      chmin(dtmin, dt);
    }

    for (auto &e : ranges) {
      e.y += get_dy(e.points, e.y, e.r, dtmin);
    }
    t += dtmin;
  }
}
