#include <bits/stdc++.h>

#include "atcoder/segtree.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;

int op(int a, int b) { return max(a, b); }
int e() { return 0; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  vector<int> lb(N);
  for (int i = 0; i < N; i++) {
    lb[i] = max(i - A[i] + 1, 0);
  }

  segtree<int, op, e> st(N);
  for (int i = 0; i < N; i++) {
    st.set(i, lb[i]);
  }

  vector<i64> ps(N + 1);
  ps[0] = 0;
  for (int i = 0; i < N; i++) {
    ps[i + 1] = ps[i] + st.prod(0, i + 1);
  }

  vector<pair<int, int>> stack;
  vector<i64> ss(N + 1);
  ss[N] = 0;
  for (int i = N - 1; i >= 0; i--) {
    ss[i] = ss[i + 1];
    int len = 1;
    while (stack.size() > 0 and stack.back().first < lb[i]) {
      auto [v, vlen] = stack.back();
      ss[i] -= (i64) v * vlen;
      len += vlen;
      stack.pop_back();
    }
    stack.push_back({lb[i], len});
    ss[i] += (i64) lb[i] * len;
  }

  int Q;
  cin >> Q;

  while (Q--) {
    int p, x;
    cin >> p >> x;
    p--;

    int lbp = max(st.prod(0, p), p - x + 1);

    int l = p + 1, r = N;
    while (l < r) {
      int m = l + (r - l + 1) / 2;
      st.prod(p + 1, m) < lbp ? l = m : r = m - 1;
    }

    i64 ans = (i64) N * (N + 1) / 2;
    ans -= ps[p] + (i64) lbp * (l - p) + ss[l];
    cout << ans << '\n';
  }
}
