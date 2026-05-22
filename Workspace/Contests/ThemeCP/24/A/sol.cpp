#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "ethankim8683/geometry.hpp"
using namespace ethankim8683;

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

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // convex hull
  //
  // try all edges

  int N;
  double R;
  cin >> N >> R;

  vc<vec2<int>> points(N);
  for (auto &e : points) {
    cin >> e;
  }

  cout << setprecision(12) << fixed;

  if (N == 1) {
    cout << PI * R * R / 2 << '\n';
    exit(0);
  }

  auto indices = convex_hull(points);
  double ans = 0;
  rep(i, 0, sz(indices)) {
    vec2<double> a = points[indices[i]],
                 b = points[indices[(i + 1) % sz(indices)]];
    double area1 = max(halfplane_circle_ixn_area(a, b - a, {0, 0}, R),
                       PI * R * R / 2),
           area2 = PI * R * R - area1;
    chmax(ans, min(area1, area2));
  }
  cout << ans << '\n';
}
