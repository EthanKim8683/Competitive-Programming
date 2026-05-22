#include <bits/stdc++.h>

#include "atcoder/lazysegtree.hpp"

using namespace std;
using namespace atcoder;

const int INF = 1e9;

struct S {
  int psl, psr, sum;
};
S op(S a, S b) {
  return {
    min(a.psl, b.psl),
    max(a.psr, b.psr),
    max(a.sum, max(b.sum, b.psr - a.psl)),
  };
}
S e() { return {INF, -INF, -INF}; }
struct F {
  int dpsl, dpsr;
};
S mapping(F f, S x) {
  return {
    x.psl + f.dpsl,
    x.psr + f.dpsr,
    x.sum + f.dpsr - f.dpsl,
  };
}
F composition(F f, F g) {
  return {
    f.dpsl + g.dpsl,
    f.dpsr + g.dpsr,
  };
}
F id() { return {0, 0}; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    for (auto &e : A) {
      cin >> e;
      e--;
    }

    vector<vector<int>> by_A(N);
    for (int i = 0; i < N; i++) {
      by_A[A[i]].push_back(i);
    }

    lazy_segtree<S, op, e, F, mapping, composition, id> st1(N - K + 1),
        st2(N - K + 1);
    auto init = [&](auto &st) -> void {
      for (int i = 0; i < N - K + 1; i++) {
        st.set(i, {0, 0, 0});
      }
    };
    auto add = [&](auto &st, int i, int x) -> void {
      st.apply(min(i + 1, N - K + 1), N - K + 1, {x, 0});
      st.apply(max(i + 1 - K, 0), N - K + 1, {0, x});
    };
    auto max_left = [&](auto &st, int r, auto g) -> int {
      int l = st.min_left(r, [&](S x) -> bool { return !g(x); });
      if (!g(st.prod(l, r))) {
        l--;
      }
      return l;
    };
    auto min_right = [&](auto &st, int l, auto g) -> int {
      int r = st.max_right(l, [&](S x) -> bool { return !g(x); });
      if (!g(st.prod(l, r))) {
        r++;
      }
      return r;
    };

    init(st1);
    init(st2);
    for (int i = 0; i < N; i++) {
      add(st1, i, -1);
      add(st2, i, 1);
    }
    vector<tuple<int, int, int>> ans;
    for (int i = 0; i < N; i++) {
      for (auto e : by_A[i]) {
        add(st1, e, 2);
      }

      auto g = [&](S x) -> bool { return x.sum >= 0; };
      if (g(st1.all_prod()) and g(st2.all_prod())) {
        int l = min(max_left(st1, N - K + 1, g), max_left(st2, N - K + 1, g)),
            r = max(min_right(st1, l, g), min_right(st2, l, g));
        if (g(st1.prod(l, r)) and g(st2.prod(l, r))) {
          ans.emplace_back(i, l, r - 1 + K);
        }
      }

      for (auto e : by_A[i]) {
        add(st2, e, -2);
      }
    }

    cout << ans.size() << '\n';
    for (auto [x, l, r] : ans) {
      cout << x + 1 << ' ' << l + 1 << ' ' << r << '\n';
    }
  }
}
