#ifndef U
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

const int INF = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

pair<int, vi> hungarian(const vc<vi> &a) {
  if (a.empty()) return {0, {}};
  int n = sz(a) + 1, m = sz(a[0]) + 1;
  vi u(n), v(m), p(m), ans(n - 1);
  rep(i, 1, n) {
    p[0] = i;
    int j0 = 0;
    vi dist(m, LLONG_MAX), pre(m, -1);
    vc<bool> done(m + 1);
    do {
      done[j0] = true;
      int i0 = p[j0], j1, delta = LLONG_MAX;
      rep(j, 1, m) if (!done[j]) {
        auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
        if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
        if (dist[j] < delta) delta = dist[j], j1 = j;
      }
      rep(j, 0, m) {
        if (done[j])
          u[p[j]] += delta, v[j] -= delta;
        else
          dist[j] -= delta;
      }
      j0 = j1;
    } while (p[j0]);
    while (j0) {
      int j1 = pre[j0];
      p[j0] = p[j1], j0 = j1;
    }
  }
  rep(j, 1, m) if (p[j]) ans[p[j] - 1] = j - 1;
  return {-v[0], ans};
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // assume n > 2
  //
  // if they're all colinear and n is odd, there's no solution
  //
  // if they're all initially colinear and n is odd, move one
  //
  // otherwise, move none
  //
  // now it's all about redirecting the sentries
  //
  // we can use min cost matching to redirect the sentries optimally
  //
  // back to the initially colinear case

  int N;
  cin >> N;

  vc<tuple<int, int, int, int, int, int>> sentries(N);
  for (auto &[x, y, z, vx, vy, vz] : sentries) {
    cin >> x >> y >> z >> vx >> vy >> vz;
  }

  if (N == 1) {
    cout << "-1\n";
    exit(0);
  }

  auto is_colinear = [&](tuple<int, int, int> p1, tuple<int, int, int> p2,
                         tuple<int, int, int> p3) -> bool {
    auto [x1, y1, z1] = p1;
    auto [x2, y2, z2] = p2;
    auto [x3, y3, z3] = p3;
    // (x3 - x2) / (x2 - x1) = (y3 - y2) / (y2 - y1) = (z3 - z2) / (z2 - z1);
    int wx = (x3 - x1) * (y2 - y1) * (z2 - z1),
        wy = (x2 - x1) * (y3 - y1) * (z2 - z1),
        wz = (x2 - z1) * (y2 - y1) * (z3 - z1);
    return wx == wy and wy == wz;
  };

  auto get_t = [&](tuple<int, int, int> p1, tuple<int, int, int> p2,
                   tuple<int, int, int> v1) -> int {
    auto [x1, y1, z1] = p1;
    auto [x2, y2, z2] = p2;
    auto [vx1, vy1, vz1] = v1;
    // (x2 - x1) / vx1 = (y2 - y1) / vy1 = (z2 - z1) / vz1
    int wx = (x2 - x1) * vy1 * vz1, wy = vx1 * (y2 - y1) * vz1,
        wz = vx1 * vy1 * (z2 - z1);
    if (!(wx == wy and wy == wz)) return -1;
    int t = (x2 - x1) / vx1;
    if (t < 0) return -1;
    return t;
  };

  auto is_reachable = [&](int i, int j) -> bool {
    auto [x1, y1, z1, vx1, vy1, vz1] = sentries[i];
    auto [x2, y2, z2, vx2, vy2, vz2] = sentries[j];
    int t = get_t({x1, y1, z1}, {x2, y2, z2}, {vx1, vy1, vz1});
    if (t == -1) return false;
    rep(k, 0, N) {
      if (k == i or k == j) continue;
      auto [x3, y3, z3, vx3, vy3, vz3] = sentries[k];
      int t2 = get_t({x1, y1, z1}, {x3, y3, z3}, {vx1, vy1, vz1});
      if (t2 == -1) continue;
      if (t2 < t) return false;
    }
    return true;
  };

  bool is_all_colinear = true;
  rep(i, 2, N) {
    auto [x1, y1, z1, vx1, vy1, vz1] = sentries[0];
    auto [x2, y2, z2, vx2, vy2, vz2] = sentries[1];
    auto [x3, y3, z3, vx3, vy3, vz3] = sentries[i];
    is_all_colinear = is_all_colinear and
                      is_colinear({x1, y1, z1}, {x2, y2, z2}, {x3, y3, z3});
  }
  if (is_all_colinear and N % 2 == 1) {
  } else {
    vc adj(N, vi(N, INF));
    rep(i, 0, N) {
      rep(j, 0, N) {
        if (i == j) continue;
        if (is_reachable(i, j)) {
          adj[i][j] = 0;
        } else {
          adj[i][j] = 1;
        }
      }
    }
    cout << hungarian(adj).fs << '\n';
  }
}
