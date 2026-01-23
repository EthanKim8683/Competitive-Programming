#pragma GCC optimize("Ofast,unroll-loops")
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

using i128 = __int128;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // start: 1:26
  // thinking done: 1:30
  // target impl time: 1hr
  // initial impl done:

  int MX, MY;
  cin >> MX >> MY;
  if (MY > MX) {
    swap(MX, MY);
  }

  auto ceil_div = [&](int x, int y) -> int {
    return x / y + (x % y != 0 and (x < 0) == (y < 0));
  };

  auto triangle = [&](int n) -> int { return n * (n - 1) / 2; };

  int R = 0, O = 0;
  rep(x2, -MX, MX + 1) {
    rep(y2, -MY, MY + 1) {
      pii V1 = {x2, y2}, V2 = {-y2, x2};
      rep(y3, -MY, MY + 1) {
        auto lower_bound = [&](pii V, int s) -> int {
          if (s == 1) return -MX;

          int rv = ceil_div(V.fs * y3, V.sd);
          if (s == -1 and rv * V.sd == V.fs * y3) {
            return min(rv + 1, MX + 1);
          }

          return min(rv, MX + 1);
        };

        auto range = [&](int x3, int x4) -> int {
          int xmin = min(0ll, x2), xmax = max(0ll, x2),
              ymin = min(0ll, min(y2, y3)), ymax = max(0ll, max(y2, y3));

          int xn = max(MX + 1 - (xmax - xmin), 0ll),
              yn = max(MY + 1 - (ymax - ymin), 0ll);

          int x5 = xmin, x6 = xmax + 1, x7 = x5 - xn, x8 = x6 + xn;

          int rv = 0;
          rv += max(min(x4, x6) - max(x3, x5), 0ll) * xn;
          rv += triangle(clamp(x4, x7, x5) - x7) -
                triangle(clamp(x3, x7, x5) - x7);
          rv += triangle(x8 - clamp(x3, x6, x8)) -
                triangle(x8 - clamp(x4, x6, x8));
          rv *= yn;

          return rv;
        };

        if (y2 < 0) {
          if (x2 < 0) {
            if (y3 < 0) {
            } else if (y3 == 0) {
            } else {
              int x3 = lower_bound(V2, 0), x4 = lower_bound(V2, -1),
                  x5 = lower_bound(V1, 0);
              R += range(x3, x4);
              O += range(x4, x5);
            }
          } else if (x2 == 0) {
            if (y3 < 0) {
            } else if (y3 == 0) {
              int x3 = -MX, x4 = 0;
              R += range(x3, x4);
            } else {
              int x3 = -MX, x4 = 0;
              O += range(x3, x4);
            }
          } else {
            if (y3 < 0) {
              int x3 = -MX, x4 = lower_bound(V2, 0), x5 = lower_bound(V2, -1);
              O += range(x3, x4);
              R += range(x4, x5);
            } else if (y3 == 0) {
              int x3 = -MX, x4 = 0;
              O += range(x3, x4);
            } else {
              int x3 = -MX, x4 = lower_bound(V1, 0);
              O += range(x3, x4);
            }
          }
        } else if (y2 == 0) {
          if (x2 < 0) {
            if (y3 < 0) {
            } else if (y3 == 0) {
            } else {
              int x3 = 0, x4 = 1, x5 = MX + 1;
              R += range(x3, x4);
              O += range(x4, x5);
            }
          } else if (x2 == 0) {
          } else {
            if (y3 < 0) {
              int x3 = -MX, x4 = 0, x5 = 1;
              O += range(x3, x4);
              R += range(x4, x5);
            } else if (y3 == 0) {
            } else {
            }
          }
        } else {
          if (x2 < 0) {
            if (y3 < 0) {
              int x3 = lower_bound(V1, -1), x4 = MX + 1;
              O += range(x3, x4);
            } else if (y3 == 0) {
              int x3 = 1, x4 = MX + 1;
              O += range(x3, x4);
            } else {
              int x3 = lower_bound(V2, 0), x4 = lower_bound(V2, -1),
                  x5 = MX + 1;
              R += range(x3, x4);
              O += range(x4, x5);
            }
          } else if (x2 == 0) {
            if (y3 < 0) {
              int x3 = 1, x4 = MX + 1;
              O += range(x3, x4);
            } else if (y3 == 0) {
              int x3 = 1, x4 = MX + 1;
              R += range(x3, x4);
            } else {
            }
          } else {
            if (y3 < 0) {
              int x3 = lower_bound(V1, -1), x4 = lower_bound(V2, 0),
                  x5 = lower_bound(V2, -1);
              O += range(x3, x4);
              R += range(x4, x5);
            } else if (y3 == 0) {
            } else {
            }
          }
        }
      }
    }
  }

  int D = 0;
  rep(dx, -MX, MX + 1) {
    rep(dy, -MY, MY + 1) {
      if (dy < 0 or (dy == 0 and dx < 0)) continue;
      if (gcd(abs(dx), abs(dy)) != 1) continue;

      for (int i = 2;; i++) {
        int xmin = min(0ll, i * dx), xmax = max(0ll, i * dx),
            ymin = min(0ll, i * dy), ymax = max(0ll, i * dy);

        int xn = max(MX + 1 - (xmax - xmin), 0ll),
            yn = max(MY + 1 - (ymax - ymin), 0ll);

        int w = xn * yn;
        if (w == 0) break;

        D += (i - 1) * w;
      }
    }
  }

  int N = (MX + 1) * (MY + 1);

  int A = N * (N - 1) * (N - 2) / 6 - (R + O + D);

  cout << A << '\n';
  cout << R << '\n';
  cout << O << '\n';
  cout << D << '\n';
}
