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

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M, W, H;
  cin >> N >> M >> W >> H;

  vc<pii> ceiling(N);
  for (auto &[x, y] : ceiling) {
    cin >> x >> y;
  }

  vc<pii> floor(M);
  for (auto &[x, y] : floor) {
    cin >> x >> y;
  }

  map<int, int> ceiling2, floor2;
  for (auto [x, y] : ceiling) {
    if (ceiling2.contains(x)) {
      chmin(ceiling2[x], y);
    } else {
      ceiling2.emplace(x, y);
    }
  }

  for (auto [x, y] : floor) {
    if (floor2.contains(x)) {
      chmax(floor2[x], y);
    } else {
      floor2.emplace(x, y);
    }
  }

  auto floor_div = [&](int x, int y) -> int {
    int rv = x / y;
    if (x % y != 0 and (x < 0) != (y < 0)) {
      rv -= 1;
    }
    return rv;
  };

  auto ceil_div = [&](int x, int y) -> int {
    int rv = x / y;
    if (x % y != 0 and (x < 0) == (y < 0)) {
      rv += 1;
    }
    return rv;
  };

  auto get_ceiling = [&](int x) -> int {
    int rv;
    if (ceiling2.contains(x)) {
      rv = ceiling2[x];
    } else {
      auto it = upper_bound(all(ceiling), make_pair(x, -INF));
      auto [x1, y1] = *prev(it);
      auto [x2, y2] = *it;
      rv = ceil_div((x - x1) * (y2 - y1), x2 - x1) + y1;
    }
    rv -= 1;
    if ((rv + x) % 2 != 0) {
      rv -= 1;
    }
    return rv;
  };

  auto get_floor = [&](int x) -> int {
    int rv;
    if (floor2.contains(x)) {
      rv = floor2[x];
    } else {
      auto it = upper_bound(all(floor), make_pair(x, -INF));
      auto [x1, y1] = *prev(it);
      auto [x2, y2] = *it;
      rv = floor_div((x - x1) * (y2 - y1), x2 - x1) + y1;
    }
    rv += 1;
    if ((rv + x) % 2 != 0) {
      rv += 1;
    }
    return rv;
  };

  set<int> X;
  for (auto [x, y] : ceiling) {
    X.insert(x);
  }
  for (auto [x, y] : floor) {
    X.insert(x);
  }
  int xprev = 0, ymin = 0, ymax = 0;
  for (auto e : X) {
    int d = e - xprev;
    ymin -= d;
    ymax += d;
    chmax(ymin, get_floor(e));
    chmin(ymax, get_ceiling(e));
    if (ymin > ymax) {
      cout << "impossible\n";
      exit(0);
    }
    xprev = e;
  }
  cout << ymin << ' ' << ymax << '\n';
}
