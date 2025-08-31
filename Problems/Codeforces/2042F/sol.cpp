#include <bits/stdc++.h>

#include "atcoder/lazysegtree.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;

const i64 INF = 1e18;

using S = array<array<i64, 4 + 1>, 4 + 1>;
S e() {
  S rv;
  for (int i = 0; i <= 4; i++) {
    for (int j = 0; j <= 4; j++) {
      rv[i][j] = i == j ? 0 : -INF;
    }
  }
  return rv;
}
S op(S a, S b) {
  S rv = e();
  for (int i = 0; i <= 4; i++) {
    for (int j = i; j <= 4; j++) {
      for (int k = i; k <= j; k++) {
        rv[i][j] = max(rv[i][j], a[i][k] + b[k][j]);
      }
    }
  }
  return rv;
}
using F = i64;
S mapping(F f, S x) {
  for (int i = 0; i <= 4; i++) {
    for (int j = i; j <= 4; j++) {
      for (int k = i; k < j; k++) {
        x[i][j] += (k % 2 == 0 ? -f : f);
      }
    }
  }
  return x;
}
F composition(F f, F g) { return f + g; }
F id() { return 0; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  vector<int> B(N);
  for (auto &e : B) cin >> e;

  int Q;
  cin >> Q;

  lazy_segtree<S, op, e, F, mapping, composition, id> st(N + 1);
  i64 ps = 0;
  for (int i = 0; i <= N; i++) {
    S sg = e();
    if (i < N) {
      sg[0][1] = -ps + B[i];
      sg[2][3] = -ps + B[i];
    }
    if (i - 1 >= 0) {
      sg[1][2] = ps + B[i - 1];
      sg[3][4] = ps + B[i - 1];
    }
    if (i - 1 >= 0 and i < N) {
      sg[1][3] = B[i - 1] + B[i];
    }
    st.set(i, sg);
    if (i < N) {
      ps += A[i];
    }
  }

  while (Q--) {
    int t;
    cin >> t;

    if (t == 1) {
      int p, x;
      cin >> p >> x;
      p--;
      st.apply(p + 1, N + 1, x - A[p]);
      A[p] = x;
    } else if (t == 2) {
      int p, x;
      cin >> p >> x;
      p--;
      auto sg = st.get(p);
      sg[0][1] += x - B[p];
      sg[2][3] += x - B[p];
      sg[1][3] += x - B[p];
      st.set(p, sg);
      sg = st.get(p + 1);
      sg[1][2] += x - B[p];
      sg[3][4] += x - B[p];
      sg[1][3] += x - B[p];
      st.set(p + 1, sg);
      B[p] = x;
    } else {
      int l, r;
      cin >> l >> r;
      l--;
      cout << st.prod(l, r + 1)[0][4] << '\n';
    }
  }
}
