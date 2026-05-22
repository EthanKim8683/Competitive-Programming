#include <bits/stdc++.h>

#include "atcoder/segtree.hpp"

using namespace std;
using namespace atcoder;

const int INF = 1e9;

struct T {
  int left, right, min, sum;
};
using S = array<T, 2>;

S op(S l, S r) {
  S rv = {
    {
      {
        l[0].left,
        r[0].right,
        min(l[0].min, r[0].min),
        INF,
      },
      {
        l[1].left,
        r[1].right,
        min(l[1].min, r[1].min),
        INF,
      },
    },
  };
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      auto chmin = [&](int &a, int b) -> void { a = min(a, b); };

      chmin(rv[i | j].left, l[i].sum + r[j].left);
      chmin(rv[i | j].right, l[i].right + r[j].sum);
      chmin(rv[i | j].min, l[i].right + r[j].left);
      chmin(rv[i | j].sum, l[i].sum + r[j].sum);
    }
  }
  return rv;
}

S e() { return {{{INF, INF, INF, INF}, {INF, INF, INF, INF}}}; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vector<int> A(N);
    for (auto &e : A) {
      cin >> e;
      e--;
    }

    // to find subarrays with median at least x:
    //
    // segment tree:
    // A[i] < x is 1
    // x <= A[i] is -1
    //
    // look for subarray sum <= 0
    //
    // if we could binary search for the least minimum for each median...
    //
    // the least minimum for each median increases w.r.t. median*
    //
    // to find subarrays with median at least x and minimum at most y:
    //
    // segment tree:
    // A[i] < x is {1, ...}
    // x <= A[i] is {-1, ...}
    // A[i] <= y is {..., 1}
    // y < A[i] is {..., 0}
    //
    // while we can't accomplish the target minimum, increase the target minimum
    //
    // *a smaller median allows more i s.t. A[i] < x to be included in a
    // subarray sum <= 0, meaning the set of medians allowed for the smaller
    // median is a superset of that of the larger median

    vector<vector<int>> indices(N);
    for (int i = 0; i < N; i++) {
      indices[A[i]].push_back(i);
    }

    int x = 0, y = 0;

    segtree<S, op, e> st(N);
    auto nudge = [&](int i) -> void {
      int f = A[i] < x ? 1 : -1;
      int s = A[i] <= y ? 1 : 0;

      S v = e();
      v[s] = {f, f, f, f};
      st.set(i, v);
    };

    for (int i = 0; i < N; i++) {
      nudge(i);
    }

    int ans = 0;
    for (; x < N; x++) {
      if (x - 1 >= 0) {
        for (auto i : indices[x - 1]) {
          nudge(i);
        }
      }

      while (st.all_prod()[1].min > 0) {
        y += 1;
        for (auto i : indices[y]) {
          nudge(i);
        }
      }
      ans = max(ans, x - y);
    }
    cout << ans << '\n';
  }
}