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
typedef vc<int> vi;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

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
  double dist() const { return sqrt((double) dist2()); }  // da2e77
  T cross(P a, P b) const { return (a - *this).cross(b - *this); }
  bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
  bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
  // angle to x−axis in interval [−pi, pi]
  double angle() const { return atan2(y, x); }
  P unit() const { return *this / dist(); }  // makes dist ()=1
  P perp() const { return P(-y, x); }        // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated ’a’ radians ccw around the origin
  P rotate(double a) const {
    return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
  }
  friend ostream &operator<<(ostream &os, P p) {
    return os << "(" << p.x << "," << p.y << ")";
  }
};  // f7a1ec

template <class P>
pair<int, P> lineInter(P s1, P e1, P s2, P e2) {
  auto d = (e1 - s1).cross(e2 - s2);
  if (d == 0)  // if parallel
    return {-(s1.cross(e1, s2) == 0), P(0, 0)};
  auto p = s2.cross(e1, e2), q = s2.cross(e2, s1);
  return {1, (s1 * p + e1 * q) / d};
}  // a01f81

typedef Point<double> P;
vc<P> polygonCut(const vc<P> &poly, P s, P e) {
  vc<P> res;
  rep(i, 0, sz(poly)) {
    P cur = poly[i], prev = i ? poly[i - 1] : poly.back();
    bool side = s.cross(e, cur) < 0;
    if (side != (s.cross(e, prev) < 0)) res.pb(lineInter(s, e, cur, prev).sd);
    if (side) res.pb(cur);
  }  // c8b84a
  return res;
}  // 181b05

bool half(P p) {
  assert(p.x != 0 || p.y != 0);
  return p.y > 0 || (p.y == 0 && p.x < 0);
}  // 6524db
void polarSort(vc<P> &v) {
  sort(v.begin(), v.end(), [](P v, P w) {
    return make_tuple(half(v), 0) < make_tuple(half(w), v.cross(w));
  });
}  // 3f533a

// double area(P a, P b, P c) { return (b-a).cross(c-a); }
// double perpArea(P a, P b, P c) { return (b-a).dot(c-a); }
// vc<vc<P>> boundingBoxes(const vc<P> &ch) {
// 	int n = sz(ch), j = 1, k, l;
// 	vc<vc<P>> res(n);
// 	rep(i, 0, n) {
// 		while (area(ch[i], ch[(i+1)%n], ch[(j+1)%n]) > area(ch[i],
// ch[(i+1)%n], ch[j])) j = (j+1)%n; 		if (i == 0) k = i, l = j;
// while (perpArea(ch[i], ch[(i+1)%n], ch[(k+1)%n]) > perpArea(ch[i],
// ch[(i+1)%n], ch[k])) k = (k+1)%n; 		while (perpArea(ch[i],
// ch[(i+1)%n], ch[(l+1)%n]) < perpArea(ch[i], ch[(i+1)%n], ch[l])) l = (l+1)%n;
// P d = (ch[i]-ch[(i+1)%n]).unit(); 		double a = d.cross(ch[j]-ch[i]),
// b = d.dot(ch[k]-ch[i]), c = d.dot(ch[l]-ch[i]); 		res[i] =
// {ch[i]+d*c, ch[i]+d*b, ch[i]+d*b+d.perp()*a, ch[i]+d*c+d.perp()*a};
// 	}
// 	return res;
// }

double polygonArea(const vc<P> &v) {
  double a = v.back().cross(v[0]);
  rep(i, 0, sz(v) - 1) a += v[i].cross(v[i + 1]);
  return a;
}

P centerOfMass(const vc<P> &v) {
  int n = sz(v);
  P c{};
  rep(i, 0, n) c = c + (v[i] + v[(i + 1) % n]) * v[i].cross(v[(i + 1) % n]);
  return c / (6 * polygonArea(v));
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, D;
  cin >> N >> D;

  vc<P> pillars(N);
  for (auto &e : pillars) {
    cin >> e.x >> e.y;
  }

  vc<P> area = {P(-1e9, -1e9), P(1e9, -1e9), P(1e9, 1e9), P(-1e9, 1e9)};
  rep(i, 0, 1000) {
    P center = centerOfMass(area);

    vc<P> points(N);
    rep(i, 0, N) { points[i] = pillars[i] - center; }
    polarSort(points);

    // we can binary search for which line segment cut it off

    vc<pair<P, P>> segments;
    auto source = P(0, 0);
    for (auto dest : points) {
      auto delta = dest - source;

      auto check = [&](int i) -> bool {
        auto delta0 = segments[i].sd - segments[i].fs;
        return delta0.cross(delta) < 0;
      };
      int l = 0, r = sz(segments);
      while (l < r) {
        int m = l + (r - l) / 2;
        check(m) ? r = m : l = m + 1;
      }
      if (l == sz(segments)) {
        segments.eb(source, dest);
        source = dest;
        continue;
      }

      auto [source0, delta0] = segments[l];
    }
  }
}
