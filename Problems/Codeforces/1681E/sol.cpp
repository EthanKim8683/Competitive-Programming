#include <bits/stdc++.h>

#include "atcoder/segtree.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;

const i64 INF = 1e18;

using S = array<array<i64, 2>, 2>;
S op(S a, S b) {
  S rv;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      rv[i][j] = min(a[i][0] + b[0][j], a[i][1] + b[1][j]);
    }
  }
  return rv;
}
S e() {
  S rv;
  rv[0][0] = 0;
  rv[0][1] = INF;
  rv[1][0] = INF;
  rv[1][1] = 0;
  return rv;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  segtree<S, op, e> st(N - 2);
  int pd1x, pd2y;
  vector<array<int, 4>> doors(N - 1);
  for (int i = 0; i < N - 1; i++) {
    auto &[d1x, d1y, d2x, d2y] = doors[i];
    cin >> d1y >> d1x >> d2y >> d2x;
    d1y--, d1x--, d2y--, d2x--;

    if (i - 1 >= 0) {
      S s;
      s[0][0] = abs(d1x - pd1x) + 1;
      s[0][1] = i - pd1x + i - d2y + 1;
      s[1][1] = abs(d2y - pd2y) + 1;
      s[1][0] = i - pd2y + i - d1x + 1;
      st.set(i - 1, s);
    }

    pd1x = d1x;
    pd2y = d2y;
  }

  int M;
  cin >> M;

  while (M--) {
    int y1, x1, y2, x2;
    cin >> y1 >> x1 >> y2 >> x2;
    y1--, x1--, y2--, x2--;

    auto layer = [&](int x, int y) -> int { return max(x, y); };

    int l1 = layer(x1, y1), l2 = layer(x2, y2);
    if (l1 > l2) {
      swap(l1, l2);
      swap(x1, x2);
      swap(y1, y2);
    }

    if (l1 == l2) {
      cout << abs(x1 - x2) + abs(y1 - y2) << '\n';
      continue;
    }

    auto is_top = [&](int x, int y) -> bool { return y == layer(x, y); };
    auto is_right = [&](int x, int y) -> bool { return x == layer(x, y); };

    auto t = st.prod(l1, l2 - 1);
    auto d1 = doors[l1], d2 = doors[l2 - 1];
    int t1[2] = {
        is_top(x1, y1) ? abs(x1 - d1[0]) + 1 : l1 - y1 + l1 - d1[0] + 1,
        is_right(x1, y1) ? abs(y1 - d1[3]) + 1 : l1 - x1 + l1 - d1[3] + 1};
    int t2[2] = {is_top(x2, y2) ? abs(x2 - d2[0]) : l2 - y2 + l2 - d2[0],
                 is_right(x2, y2) ? abs(y2 - d2[3]) : l2 - x2 + l2 - d2[3]};
    i64 ans = INF;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        ans = min(ans, t1[i] + t[i][j] + t2[j]);
      }
    }
    cout << ans << '\n';
  }
}
