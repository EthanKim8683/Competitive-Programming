#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#include "atcoder/string.hpp"
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

const int LOGN = 19;
const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vi A(N);
  for (auto &e : A) cin >> e;

  // suffix array probably
  //
  // and then ranges

  vc<pii> ranges;
  for (int i = 0, j; i < N; i = j) {
    for (j = i + 1; j < N and A[j] == A[i]; j++);
    ranges.eb(i, j);
  }
  vi B;
  for (auto [l, r] : ranges) {
    if (r - l < A[l]) {
      B.pb(0);
    } else if (r - l == A[l]) {
      B.pb(A[l]);
    } else {
      B.pb(A[l]);
      B.pb(0);
      B.pb(A[l]);
    }
  }
  B.pb(0);

  auto sa = suffix_array(B), lcp = lcp_array(B, sa);

  vc<pii> pairs(sz(lcp));
  rep(i, 0, sz(lcp)) { pairs[i] = {lcp[i], i}; }

  using S = pii;
  auto op = [&](S a, S b) -> S { return min(a, b); };
  auto e = [&]() -> S { return {INF, -1}; };
  auto rmq = sparse_table<S, op, e>(pairs);

  vi reach(sz(B));
  for (int i = sz(B) - 1; i >= 0; i--) {
    if (B[i] == 0) {
      reach[i] = 0;
    } else {
      reach[i] = reach[i + 1] + 1;
    }
  }

  int ans = 0;
  auto dfs = [&](auto self, int l, int r, int n0) -> void {
    if (r - l == 1) {
      ans += reach[sa[l]] - n0;
      return;
    }

    auto [n, m] = rmq.prod(l, r - 1);
    chmin(n, reach[sa[l]]);
    ans += n - n0;

    self(self, l, m + 1, n);
    self(self, m + 1, r, n);
  };
  dfs(dfs, 0, sz(B), 0);
  cout << ans << '\n';
}
