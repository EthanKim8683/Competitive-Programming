#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/segtree.hpp"
using namespace atcoder;

#include "ethankim8683/data_structures.hpp"
using namespace ethankim8683;

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

const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // absolute max has to go in one of them
  //
  // max and 2nd max should take up as much as possible
  //
  // the smallest one is size 1
  //
  // either 1 L-2 1 or k 1 L-1-k
  //
  // each index stores, until the next value that is greater than it, what is
  // the minimum value
  //
  // this doesn't exactly give the right answer cuz a big value and a smaller
  // one after it can point to the same next value and the smaller one would
  // give a "better" answer, so we maintain a stack and process queries left to
  // right

  int N, Q;
  cin >> N >> Q;

  vi A(N);
  for (auto &e : A) cin >> e;
  A.pb(INF);

  vc<pii> queries(Q);
  for (auto &[l, r] : queries) {
    cin >> l >> r;
    l--;
  }

  vc<vi> by_left(N), by_right(N);
  rep(i, 0, Q) {
    auto [l, r] = queries[i];
    by_left[l].pb(i);
    by_right[r - 1].pb(i);
  }

  vc<pii> pairs(N);
  rep(i, 0, N) { pairs[i] = {A[i], i}; }

  using S = pii;
  auto op = [&](S a, S b) -> S { return max(a, b); };
  auto e = [&]() -> S { return {-INF, -1}; };
  sparse_table<S, op, e> rmq(pairs);

  vi ans(Q, INF);
  rep(i, 0, Q) {
    auto [l, r] = queries[i];
    chmin(ans[i], A[l] + rmq.prod(l + 1, r - 1).fs + A[r - 1]);
  }

  {
    using S = int;
    auto op = [&](S a, S b) -> S { return min(a, b); };
    auto e = [&]() -> S { return INF; };
    segtree<S, op, e> st(N);
    vi stack;
    stack.pb(N);
    for (int i = N - 1; i >= 0; i--) {
      int x = A[stack.back()];
      while (A[stack.back()] < A[i]) {
        int j = stack.back();
        stack.pop_back();
        chmin(x, st.get(j) - A[j]);
        st.set(j, e());
      }
      st.set(i, x + A[i]);
      stack.pb(i);

      for (auto j : by_left[i]) {
        auto [l, r] = queries[j];
        auto [Am, m] = rmq.prod(l, r);
        if (!(l <= m - 1)) continue;
        chmin(ans[j], st.prod(l, m - 1) + Am);
      }
    }
  }

  {
    using S = int;
    auto op = [&](S a, S b) -> S { return min(a, b); };
    auto e = [&]() -> S { return INF; };
    segtree<S, op, e> st(N);
    vi stack;
    stack.pb(N);
    rep(i, 0, N) {
      int x = A[stack.back()];
      while (A[stack.back()] < A[i]) {
        int j = stack.back();
        stack.pop_back();
        chmin(x, st.get(j) - A[j]);
        st.set(j, e());
      }
      st.set(i, x + A[i]);
      stack.pb(i);

      for (auto j : by_right[i]) {
        auto [l, r] = queries[j];
        auto [Am, m] = rmq.prod(l, r);
        if (!(m + 2 <= r)) continue;
        chmin(ans[j], Am + st.prod(m + 2, r));
      }
    }
  }

  for (auto e : ans) {
    cout << e << '\n';
  }
}
