#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "atcoder/segtree.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

const int INF = 1e9;

using S = tuple<int, int, int>;
S op(S a, S b) {
  auto [l1, r1, count1] = a;
  auto [l2, r2, count2] = b;
  return {max(l1, l2), min(r1, r2), count1 + count2};
}
S e() { return {-INF, INF, 0}; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> P(N);
    for (auto &e : P) cin >> e, e--;

    vector<int> C(N);
    for (auto &e : C) cin >> e;

    vector<int> order(N);
    for (int i = 0; i < N; i++) {
      order[P[i]] = i;
    }

    segtree<S, op, e> st(N);
    mint ans = 1;
    for (int i = N - 1; i >= 0; i--) {
      int j = order[i], c = C[j];
      st.set(j, {c, c, 1});

      auto ok = [&](tuple<int, int, int> range) -> bool {
        auto [l, r, count] = range;
        return l <= r;
      };

      int count = 0;
      {
        int l = 0, r = j;
        while (l < r) {
          int m = l + (r - l) / 2;
          ok(st.prod(m, j + 1)) ? r = m : l = m + 1;
        }
        count += get<2>(st.prod(l, j));
      }
      {
        int l = j + 1, r = N;
        while (l < r) {
          int m = l + (r - l + 1) / 2;
          ok(st.prod(j, m)) ? l = m : r = m - 1;
        }
        count += get<2>(st.prod(j, l));
      }
      ans *= count;
    }
    cout << ans.val() << '\n';
  }
}
