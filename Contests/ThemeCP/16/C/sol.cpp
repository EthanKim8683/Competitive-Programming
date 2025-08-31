#include <bits/stdc++.h>

#include "atcoder/lazysegtree.hpp"
#include "atcoder/modint.hpp"

using namespace std;
using namespace atcoder;

using mint = modint998244353;
using vec = array<mint, 2>;
using mat = array<array<mint, 2>, 2>;

vec op(vec a, vec b) { return {{0, 0}}; }
vec e() { return {{0, 0}}; }
vec mapping(mat f, vec x) {
  vec rv = {{0, 0}};
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      rv[i] += f[i][j] * x[j];
    }
  }
  return rv;
}
mat composition(mat f, mat g) {
  mat rv = {{{{0, 0}}, {{0, 0}}}};
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        rv[i][j] += f[i][k] * g[k][j];
      }
    }
  }
  return rv;
}
mat id() { return {{{{1, 0}}, {{0, 1}}}}; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int N;
  cin >> N;

  vector<pair<int, int>> segs(N);
  for (auto &[l, r] : segs) {
    cin >> l >> r;
    r++;
  }

  vector<int> cc;
  for (auto [l, r] : segs) {
    cc.push_back(l);
    cc.push_back(r);
  }
  sort(cc.begin(), cc.end());
  cc.erase(unique(cc.begin(), cc.end()), cc.end());

  for (auto &[l, r] : segs) {
    l = lower_bound(cc.begin(), cc.end(), l) - cc.begin();
    r = lower_bound(cc.begin(), cc.end(), r) - cc.begin();
  }
  int K = cc.size() - 1;

  lazy_segtree<vec, op, e, mat, mapping, composition, id> st(K);
  for (int i = 0; i < K; i++) {
    auto [l, r] = segs[0];
    vec v = {{0, 0}};
    v[l <= i and i < r] = 1;
    st.set(i, v);
  }
  for (int i = 1; i < N; i++) {
    auto [l, r] = segs[i];
    mat M0 = {{{{3, 1}}, {{0, 2}}}};
    mat M1 = {{{{1, 1}}, {{2, 2}}}};
    st.apply(0, l, M0);
    st.apply(l, r, M1);
    st.apply(r, K, M0);
  }

  mint ans = 0;
  for (int i = 0; i < K; i++) {
    ans += st.get(i)[1] * (cc[i + 1] - cc[i]);
  }
  cout << ans.val();
}
