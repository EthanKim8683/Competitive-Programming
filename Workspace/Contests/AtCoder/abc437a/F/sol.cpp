#include <bits/stdc++.h>

#include "atcoder/segtree.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, Q;
  cin >> N >> Q;

  vector<pair<int, int>> trees(N);
  for (auto &[X, Y] : trees) {
    cin >> X >> Y;
  }

  int signs[] = {-1, 1};

  auto op = [&](i64 a, i64 b) -> i64 { return max(a, b); };
  auto e = [&]() -> i64 { return -INF; };
  vector st(2, vector(2, segtree<i64, op, e>(N)));
  auto assign = [&](int i, int x, int y) -> void {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        st[j][k].set(i, (i64) x * signs[j] + (i64) y * signs[k]);
      }
    }
  };
  auto query = [&](int l, int r, int x, int y) -> i64 {
    i64 ans = 0;
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        ans = max(
            ans, st[j][k].prod(l, r) - (i64) x * signs[j] - (i64) y * signs[k]);
      }
    }
    return ans;
  };

  for (int i = 0; i < N; i++) {
    auto [X, Y] = trees[i];
    assign(i, X, Y);
  }

  while (Q--) {
    int t;
    cin >> t;

    if (t == 1) {
      int i, x, y;
      cin >> i >> x >> y;
      i--;

      assign(i, x, y);
    } else {
      int l, r, x, y;
      cin >> l >> r >> x >> y;
      l--;

      cout << query(l, r, x, y) << '\n';
    }
  }
}
