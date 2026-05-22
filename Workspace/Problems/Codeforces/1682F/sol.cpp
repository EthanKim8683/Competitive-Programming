#include <bits/stdc++.h>

#include "atcoder/modint.hpp"
#include "atcoder/segtree.hpp"

using namespace std;
using namespace atcoder;

using i64 = long long;
using mint = modint1000000007;

using S = pair<mint, mint>;
S op(S a, S b) { return {a.first + b.first, a.second + b.second}; }
S e() { return {0, 0}; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N, Q;
  cin >> N >> Q;

  vector<int> A(N);
  for (auto &e : A) cin >> e;

  vector<int> B(N);
  for (auto &e : B) cin >> e;

  vector<pair<int, int>> queries(Q);
  for (auto &[l, r] : queries) {
    cin >> l >> r;
    l--;
  }

  // no crosses
  //
  // look at the graphs sideways so that each b_i is a shift up or down on one
  // of the graphs
  //
  // there are O(N) different ways to intersect the graphs
  //
  // use sweep line and segtree to answer queries offline

  vector<i64> ps1 = {0}, ps2 = {0};
  vector<int> index1(N), index2(N);
  for (int i = 0; i < N; i++) {
    if (B[i] < 0) {
      ps1.push_back(ps1.back() + -B[i]);
    } else {
      ps2.push_back(ps2.back() + B[i]);
    }
    index1[i] = ps1.size() - 1;
    index2[i] = ps2.size() - 1;
  }

  auto cc = A;
  cc.push_back(-1e9);
  cc.push_back(2e9);
  sort(cc.begin(), cc.end());
  cc.erase(unique(cc.begin(), cc.end()), cc.end());
  auto compress = [&](int x) -> int {
    return lower_bound(cc.begin(), cc.end(), x) - cc.begin();
  };

  auto make_graph = [&](int sign) -> vector<i64> {
    vector<i64> rv(cc.size());
    i64 y = 0;
    int j = 0;
    for (int i = 0; i < N; i++) {
      if (B[i] * sign < 0) continue;
      for (; cc[j] < A[i]; j++) {
        rv[j] = y;
      }
      y += B[i] * sign;
    }
    for (; j < cc.size(); j++) {
      rv[j] = y;
    }
    return rv;
  };
  auto G1 = make_graph(-1), G2 = make_graph(1);
  i64 d = 0;
  for (int i = 0; i < cc.size(); i++) {
    d = min(d, G2[i] - G1[i]);
  }
  for (auto &e : G2) {
    e += -d;
  }

  vector<pair<int, int>> queries2(Q);
  for (int i = 0; i < Q; i++) {
    auto [l, r] = queries[i];
    queries2[i] = {compress(A[l]), compress(A[r - 1])};
  }

  vector<tuple<i64, int, int>> events;
  for (int i = 0; i + 1 < cc.size(); i++) {
    events.push_back({G2[i] - G1[i], 1, i});
  }
  for (int i = 0; i < Q; i++) {
    int j = queries[i].first;
    events.push_back({ps2[index2[j]] + -d - ps1[index1[j]] - B[j], 2, i});
  }
  sort(events.begin(), events.end());

  segtree<S, op, e> st(cc.size() - 1);
  for (int i = 0; i + 1 < cc.size(); i++) {
    mint w = cc[i + 1] - cc[i];
    st.set(i, {-w, (G2[i] - G1[i]) * w});
  }

  vector<mint> ans(Q);
  for (auto [t, s, i] : events) {
    if (s == 1) {
      auto [m1, b1] = st.get(i);
      mint w = cc[i + 1] - cc[i], m2 = w, b2 = (m1 - m2) * t + b1;
      st.set(i, {m2, b2});
    } else {
      auto [l, r] = queries2[i];
      auto [m, b] = st.prod(l, r);
      ans[i] = m * t + b;
    }
  }

  for (auto e : ans) {
    cout << e.val() << '\n';
  }
}
