#include <bits/stdc++.h>

#include "atcoder/segtree.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;

using S = int;
S op(S a, S b) { return max(a, b); }
S e() { return -1; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  segtree<S, op, e> st(1e5);
  while (T--) {
    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    for (auto &e : A) cin >> e, e--;

    vector<vector<int>> segs(2 * N);
    for (int i = 0; i < N; i++) {
      segs[i + N].push_back(A[i]);
    }
    for (int i = N - 1; i > 0; i--) {
      merge(segs[i << 1].begin(), segs[i << 1].end(), segs[i << 1 | 1].begin(),
            segs[i << 1 | 1].end(), back_inserter(segs[i]));
    }
    auto query = [&](int l, int r, int x) -> int {
      int rv = 0;
      auto use = [&](int i) -> void {
        rv += lower_bound(segs[i].begin(), segs[i].end(), x) - segs[i].begin();
      };
      for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1) use(l++);
        if (r & 1) use(--r);
      }
      return rv;
    };

    vector<int> L(N, 0), R(N, 0);
    i64 ans = 0;
    for (int i = 0; i < N; i++) {
      int j1 = st.prod(max(A[i] - K, 0), A[i]),
          j2 = st.prod(A[i] + 1, min(A[i] + K + 1, (int) 1e5));
      if (j1 != -1) {
        L[i] += L[j1];
      }
      if (j2 != -1) {
        R[i] += R[j2];
      }
      L[i] += query(j1 + 1, i + 1, A[i] - K);
      R[i] += query(j2 + 1, i + 1, A[i] + K + 1);
      ans += R[i] - L[i];
      st.set(A[i], i);
    }
    cout << ans << '\n';

    for (auto i : A) {
      st.set(i, e());
    }
  }
}
