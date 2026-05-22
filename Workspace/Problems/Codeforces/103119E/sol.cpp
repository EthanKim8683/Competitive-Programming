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

struct rect {
  int x, y, w, h;
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 6:39
  // thinking done: 6:43
  // target impl time: 30 min
  // initial impl done:

  // dynamic programming

  int N, W, H;
  cin >> N >> W >> H;

  vi h(N + 2);
  h[0] = h[N + 1] = 0;
  rep(i, 1, N + 1) { cin >> h[i]; }

  auto area = [&](rect r) -> double {
    double rv = 0;
    rep(i, 0, r.w) {
      int a = h[r.x + i], b = h[r.x + i + 1];
      if (a > b) {
        swap(a, b);
      }

      auto ps = [&](int y) -> double {
        if (y < a) {
          return y;
        } else if (y < b) {
          return a + (1 + (double) (b - y) / (b - a)) / 2 * (y - a);
        } else {
          return a + (double) (b - a) / 2;
        }
      };
      rv += ps(r.y + r.h) - ps(r.y);
    }
    return rv;
  };

  auto intersection = [&](rect r1, rect r2) -> rect {
    int x1 = max(r1.x, r2.x), x2 = min(r1.x + r1.w, r2.x + r2.w),
        y1 = max(r1.y, r2.y), y2 = min(r1.y + r1.h, r2.y + r2.h);
    return {x1, y1, max(x2 - x1, 0ll), max(y2 - y1, 0ll)};
  };
}
