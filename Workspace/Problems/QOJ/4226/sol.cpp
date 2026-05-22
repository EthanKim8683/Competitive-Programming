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

  // basically if x or y is more than half, just make it full and the other keep
  //
  // otherwise, get double area by just making x = 2x, y = 2y

  int N, M;
  cin >> N >> M;

  vc<pii> chips(M);
  for (auto &[x, y] : chips) {
    cin >> x >> y;
  }

  auto delta = [&](pii p1, pii p2) -> pii {
    auto [x1, y1] = p1;
    auto [x2, y2] = p2;
    return {x2 - x1, y2 - y1};
  };

  auto cross = [&](pii v1, pii v2) -> int {
    auto [x1, y1] = v1;
    auto [x2, y2] = v2;
    return x1 * y2 - x2 * y1;
  };

  auto less = [&](pii v1, pii v2) -> bool {
    auto half = [&](pii v) -> int { return v > pair{0, 0}; };
    auto key = [&](pii v) -> pii { return {half(v), cross(v1, v)}; };
    return key(v1) < key(v2);
  };

  rep(i, 0, M) {
    vi order;
    rep(j, 0, M) {
      if (j == i) continue;
      order.pb(j);
    }
    sort(all(order), [&](int a, int b) -> bool {
      return less(delta(chips[i], chips[a]), delta(chips[i], chips[b]));
    });

    rep(j, 0, 2 * sz(order)) {}
  }
}
