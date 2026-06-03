#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/lazysegtree.hpp"
using namespace atcoder;

#define int long long
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second
typedef pair<int, int> pii;
typedef vc<int> vi;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // min stays 0

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vc<pii> ranges(N);
    for (auto &[l, r] : ranges) {
      cin >> l >> r;
      l--;
    }

    vi cc;
    cc.pb(0);
    cc.pb(M);
    for (auto [l, r] : ranges) {
      cc.pb(l);
      cc.pb(r);
    }
    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());
    for (auto &[l, r] : ranges) {
      l = lower_bound(all(cc), l) - cc.begin();
      r = lower_bound(all(cc), r) - cc.begin();
    }

    vc<vi> by_r(sz(cc) + 1), by_l(sz(cc) + 1);
    for (auto [l, r] : ranges) {
      by_r[r].pb(l);
      by_l[l].pb(r);
    }

    int ans = 0;
    using S = int;
    auto op = [&](S a, S b) -> S { return max(a, b); };
    auto e = [&]() -> S { return 0; };
    using F = int;
    auto mapping = [&](F f, S x) -> S { return x + f; };
    auto composition = [&](F f, F g) -> F { return f + g; };
    auto id = [&]() -> F { return 0; };
    lazy_segtree<S, op, e, F, mapping, composition, id> st(sz(cc));
    rep(i, 0, sz(cc) - 1) {
      for (auto e : by_r[i]) {
        st.apply(e, i, 1);
      }
      chmax(ans, st.all_prod());
    }
    st = lazy_segtree<S, op, e, F, mapping, composition, id>(sz(cc));
    for (int i = sz(cc) - 2; i >= 0; i--) {
      for (auto e : by_l[i + 1]) {
        st.apply(i + 1, e, 1);
      }
      chmax(ans, st.all_prod());
    }
    cout << ans << '\n';
  }
}
