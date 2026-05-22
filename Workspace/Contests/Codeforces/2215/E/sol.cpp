#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "ethankim8683/utils.hpp"

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

const int INF = 1e18;
const pii NIL = {INF, INF};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // sweep line, additional point must be no more extreme to furthest point than
  // second furthest point? if more extreme than max, can't get. else can get
  //
  // if more extreme than max, pick new max. not full picture: picks all on my
  // side of max. if more extreme, don't use it yet, but can use later if find
  // one less extreme?
  //
  // should we always pick start? actually yes cuz any other start option w/
  // diff result could be used with it for an additional triangle
  //
  // okay so greedy works i think: start from max. frontier should be monotonic,
  // so get what you can

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vc<pii> stars(N);
    for (auto &[x, y] : stars) {
      cin >> x >> y;
    }
    map<pii, int> indices;
    rep(i, 0, N) { indices[stars[i]] = i; }
    sort(all(stars));

    auto is_ok = [&](pii a, pii b, pii c) -> bool {
      auto [x1, y1] = a;
      auto [x2, y2] = b;
      auto [x3, y3] = c;
      int xmin = min(x1, min(x2, x3)), ymin = min(y1, min(y2, y3)),
          xmax = max(x1, max(x2, x3)), ymax = max(y1, max(y2, y3));
      int count = 0;
      if (x1 == xmin or y1 == ymin or x1 == xmax or y1 == ymax) {
        count += 1;
      }
      if (x2 == xmin or y2 == ymin or x2 == xmax or y2 == ymax) {
        count += 1;
      }
      if (x3 == xmin or y3 == ymin or x3 == xmax or y3 == ymax) {
        count += 1;
      }
      return count == 3;
    };

    map<int, int> by_y;
    int yprev = -1;
    vc<tuple<pii, pii, pii>> ans;
    for (auto [x, y] : stars) {
      if (yprev != -1) {
        if (y < yprev) {
          pii a = {x, y}, b, c = NIL;
          vi erase;
          auto it = make_reverse_iterator(next(by_y.find(yprev)));
          while (it != by_y.rend()) {
            b = c;
            c = {it->sd, it->fs};
            it++;
            if (b != NIL) {
              if (!is_ok(a, b, c)) break;
              ans.eb(a, b, c);
              if (c.sd > y) {
                erase.pb(c.sd);
              }
            }
          }
          for (auto e : erase) {
            by_y.erase(e);
          }
        } else {
          pii a = {x, y}, b, c = NIL;
          vi erase;
          auto it = by_y.find(yprev);
          while (it != by_y.end()) {
            b = c;
            c = {it->sd, it->fs};
            it++;
            if (b != NIL) {
              if (!is_ok(a, b, c)) break;
              ans.eb(a, b, c);
              if (c.sd < y) {
                erase.pb(c.sd);
              }
            }
          }
          for (auto e : erase) {
            by_y.erase(e);
          }
        }
      }
      by_y[y] = x;
      yprev = y;
    }

    viz([&]() -> void {
      for (auto [a, b, c] : ans) {
        auto draw_line = [&](pii a, pii b) -> void {
          DrawLine(200 + a.fs * 10, 200 + a.sd * 10, 200 + b.fs * 10,
                   200 + b.sd * 10, RED);
        };
        draw_line(a, b);
        draw_line(a, c);
        draw_line(b, c);
      }
    });

    cout << sz(ans) << '\n';
    for (auto [a, b, c] : ans) {
      cout << indices[a] + 1 << ' ' << indices[b] + 1 << ' ' << indices[c] + 1
           << '\n';
    }
  }
}
