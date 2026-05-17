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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // R must be even
  //
  // is there always a solution then? (discounting trivial cases)
  //
  // if R is 0, then B must be even
  //
  // else, we can always find a solution
  //
  //   >v
  //  >^v
  // >^v<
  // ^<<
  //
  //   \
  //  / /
  // / /
  //  \
  //
  //  >>v
  // >^v<
  // ^<<
  //
  //  >>/
  // / /
  //  \

  int T;
  cin >> T;

  while (T--) {
    int R, B;
    cin >> R >> B;

    if (R % 2 != 0) {
      cout << "No\n";
      continue;
    }

    if (R == 2 and B == 0) {
      cout << "Yes\nR 1 1\nR 2 1\n";
      continue;
    }

    vc<tuple<char, int, int>> ans;
    int n = B + R / 2, r = 0, b = 0, x = 0, y = 0;
    if (n % 2 == 0) {
      rep(i, 0, n / 2 - 1) {
        if (R - r >= 2) {
          ans.eb('R', x, y);
          y += 1;
          ans.eb('R', x, y);
          x += 1;
          r += 2;
        } else {
          ans.eb('B', x, y);
          x += 1;
          y += 1;
          b += 1;
        }
      }
      if (R - r >= 2) {
        ans.eb('R', x, y);
        x += 1;
        ans.eb('R', x, y);
        y -= 1;
        r += 2;
      } else {
        ans.eb('B', x, y);
        x += 1;
        y -= 1;
        b += 1;
      }
      rep(i, 0, n / 2 - 1) {
        if (R - r >= 2) {
          ans.eb('R', x, y);
          y -= 1;
          ans.eb('R', x, y);
          x -= 1;
          r += 2;
        } else {
          ans.eb('B', x, y);
          x -= 1;
          y -= 1;
          b += 1;
        }
      }
      if (R - r >= 2) {
        ans.eb('R', x, y);
        x -= 1;
        ans.eb('R', x, y);
        y += 1;
        r += 2;
      } else {
        ans.eb('B', x, y);
        x -= 1;
        y += 1;
        b += 1;
      }
    } else {
      if (R == 0) {
        cout << "No\n";
        continue;
      }
      rep(i, 0, (n - 1) / 2 - 1) {
        if (R - r >= 4) {
          ans.eb('R', x, y);
          y += 1;
          ans.eb('R', x, y);
          x += 1;
          r += 2;
        } else {
          ans.eb('B', x, y);
          x += 1;
          y += 1;
          b += 1;
        }
      }
      ans.eb('R', x, y);
      x += 1;
      ans.eb('R', x, y);
      x += 1;
      r += 2;
      rep(i, 0, (n + 1) / 2 - 1) {
        if (R - r >= 2) {
          ans.eb('R', x, y);
          y -= 1;
          ans.eb('R', x, y);
          x -= 1;
          r += 2;
        } else {
          ans.eb('B', x, y);
          x -= 1;
          y -= 1;
          b += 1;
        }
      }
      if (R - r >= 2) {
        ans.eb('R', x, y);
        x -= 1;
        ans.eb('R', x, y);
        y += 1;
        r += 2;
      } else {
        ans.eb('B', x, y);
        x -= 1;
        y += 1;
        b += 1;
      }
    }
    assert(x == 0 and y == 0);
    cout << "Yes\n";
    for (auto [p, r, c] : ans) {
      cout << p << ' ' << r + 2 << ' ' << c + 2 << '\n';
    }
  }
}
