#include <bits/stdc++.h>

#include "atcoder/segtree.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;

const i64 INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) cin >> e;

    vector<i64> ps(N + 1);
    ps[0] = 0;
    for (int i = 0; i < N; i++) {
      ps[i + 1] = ps[i] + A[i];
    }

    auto check = [&](i64 x) -> bool {
      segtree<i64, [](i64 a, i64 b) { return min(a, b); }, []() { return INF; }>
          st(N + 1);
      st.set(0, 0);
      for (int i = 0; i < N; i++) {
        int j = lower_bound(ps.begin(), ps.end(), ps[i] - x) - ps.begin();
        st.set(i + 1, st.prod(j, i + 1) + A[i]);
      }
      int i = lower_bound(ps.begin(), ps.end(), ps[N] - x) - ps.begin();
      return st.prod(i, N + 1) <= x;
    };

    i64 l = 0, r = 1e14;
    while (l < r) {
      i64 m = l + (r - l) / 2;
      check(m) ? r = m : l = m + 1;
    }
    cout << l << '\n';
  }
}
