#include <bits/stdc++.h>

#include "atcoder/lazysegtree.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  // add dynamic on i, static on i+1
  // add dynamic on i, dynamic on i+1
  // add static on i, dynamic on i+1

  int T;
  cin >> T;

  while (T--) {
    int N, M, K;
    cin >> N >> M >> K;

    vector A(N, vector<int>(M));
    for (auto &r : A) {
      for (auto &e : r) {
        cin >> e;
        if (e != -1) {
          e--;
        }
      }
    }

    for (int i = 0; i < N; i++) {
      sort(A[i].begin(), A[i].end());
    }
    auto count = [&](int i, int c) -> int {
      return upper_bound(A[i].begin(), A[i].end(), c) -
             lower_bound(A[i].begin(), A[i].end(), c);
    };

    i64 base = 0;
    for (int i = 0; i + 1 < N; i++) {
      for (auto e : A[i]) {
        if (e == -1) continue;
        base += count(i + 1, e);
      }
    }

    using S = i64;
    auto op = [&](S a, S b) -> S { return max(a, b); };
    auto e = [&]() -> S { return -INF; };
    using F = pair<i64, i64>;
    auto mapping = [&](F f, S x) -> S {
      auto [chmax, add] = f;
      return max(x, chmax) + add;
    };
    auto composition = [&](F f, F g) -> F {
      auto [chmax1, add1] = f;
      auto [chmax2, add2] = g;
      return {max(chmax2, chmax1 - add2), add2 + add1};
    };
    auto id = [&]() -> F { return {-INF, 0}; };
    lazy_segtree<S, op, e, F, mapping, composition, id> st(K);
    for (int i = 0; i < K; i++) {
      st.set(i, base);
    }
    auto chmax = [&](int l, int r, i64 chmax) -> void {
      st.apply(l, r, {chmax, 0});
    };
    auto add = [&](int l, int r, i64 add) -> void {
      st.apply(l, r, {-INF, add});
    };

    for (int i = 0; i + 1 < N; i++) {
      for (auto e : A[i + 1]) {
        if (e == -1) continue;
        add(e, e + 1, count(i, -1));
      }

      i64 v = st.all_prod();
      add(0, K, (i64) count(i, -1) * count(i + 1, -1));
      chmax(0, K, v);

      for (auto e : A[i]) {
        if (e == -1) continue;
        add(e, e + 1, count(i + 1, -1));
      }
    }
    cout << st.all_prod() << '\n';
  }
}
