#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

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

const int LOGA = 60;
const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // cartesian tree
  //
  // num ops, max

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi B(N);
    for (auto &e : B) cin >> e;

    vc<pii> pairs(N);
    rep(i, 0, N) { pairs[i] = {B[i], i}; }

    using S = pii;
    auto op = [&](S a, S b) -> S { return min(a, b); };
    auto e = [&]() -> S { return {INF, -1}; };
    sparse_table<S, op, e> rmq(pairs);

    auto dfs = [&](auto self, int l, int r) -> vi {
      if (l == r) return vi(LOGA + 1, 1);
      auto [Bm, m] = rmq.prod(l, r);
      auto dpl = self(self, l, m), dpr = self(self, m + 1, r);
      vi dp(LOGA + 1, INF);
      rep(i, 0, LOGA + 1) {
        rep(j, 0, LOGA + 1 - i) { chmin(dp[i + j], max(dpl[i], dpr[j])); }
      }
      for (auto &e : dp) {
        chmax(e, A[m]);
      }
      rep(i, 0, LOGA) { chmin(dp[i + 1], (dp[i] + Bm - 1) / Bm); }
      return dp;
    };
    auto dp = dfs(dfs, 0, N);
    int ans = INF;
    rep(i, 0, LOGA + 1) {
      if (dp[i] != 1) continue;
      chmin(ans, i);
    }
    cout << ans << '\n';
  }
}
