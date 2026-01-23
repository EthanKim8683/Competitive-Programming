#include <iostream>
#ifndef L
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#define int long long
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

const int MOD = 998244353;

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
  // angle to x−axis in i n t e r v a l [−pi , pi ]
  double angle() const { return atan2(y, x); }
  P unit() const { return *this / dist(); }  // makes d i s t ()=1
  P perp() const { return P(-y, x); }        // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated ’a ’ radians ccw around the origin
  P rotate(double a) const {
    return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
  }
  friend ostream &operator<<(ostream &os, P p) {
    return os << "(" << p.x << "," << p.y << ")";
  }
};  // f7a1ec

using P = Point<int>;

bool half(P p) {
  assert(p.x != 0 || p.y != 0);
  return p.y > 0 || (p.y == 0 && p.x < 0);
}  // 6524db
void polarSort(vc<P> &v) {
  sort(all(v), [](P v, P w) {
    return make_tuple(half(v), 0) < make_tuple(half(w), v.cross(w));
  });
}  // 858075

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vc<P> points(N);
  for (auto &[x, y] : points) {
    cin >> x >> y;
  }
  polarSort(points);

  auto is_ok = [&](int a, int b) -> bool {
    P p1 = points[a], p2 = points[b];
    int d1 = (p2 - p1).dist2(), d2 = (p1 - P(0, 0)).dist2(),
        d3 = (p2 - P(0, 0)).dist2();
    return d2 < d1 and d3 < d1;
  };

  vc dp(2, vc(N, vi(N, 0)));
  rep(i, 0, N) {
    (dp[(i + 1) % 2][i][i] += 1) %= MOD;

    rep(j, 0, i) {
      rep(k, 0, i) {
        (dp[(i + 1) % 2][j][k] += dp[i % 2][j][k]) %= MOD;

        if (is_ok(k, i)) {
          (dp[(i + 1) % 2][j][i] += dp[i % 2][j][k]) %= MOD;
        }

        dp[i % 2][j][k] = 0;
      }
    }
  }
  int ans = 0;
  rep(i, 0, N) {
    rep(j, i, N) {
      if (i == j or is_ok(i, j)) {
        (ans += dp[N % 2][i][j]) %= MOD;
      }
    }
  }
  cout << ans << '\n';
}
