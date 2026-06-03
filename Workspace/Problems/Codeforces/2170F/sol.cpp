#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

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

const int LOGA = 12;
const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // xor basis
  //
  // dependent vectors
  //
  // construct and then use dependent vectors?
  //
  // dnc xor sum?
  //
  // maybe 12 vectors -> try pairing
  //
  // grow right bound: maintain maximum left bound for each set size
  //
  // 12 * 2^12... this could work

  int N;
  cin >> N;

  vi A(N);
  for (auto &e : A) cin >> e;

  int Q;
  cin >> Q;

  vc<tuple<int, int, int>> queries(Q);
  for (auto &[l, r, x] : queries) {
    cin >> l >> r >> x;
    l--;
  }

  vc<vi> by_r(N + 1);
  rep(i, 0, Q) {
    auto [l, r, x] = queries[i];
    by_r[r].pb(i);
  }

  vc dp(1 << LOGA, vi(LOGA + 1, -INF));
  vi ans(Q);
  rep(i, 0, N) {
    rep(j, 0, LOGA + 1) { chmax(dp[0][j], i); }
    rep(j, 0, 1 << LOGA) {
      rep(k, 0, LOGA) { chmax(dp[j ^ A[i]][k + 1], dp[j][k]); }
    }

    for (auto j : by_r[i + 1]) {
      auto [l, r, x] = queries[j];
      ans[j] = INF;
      rep(i, 0, LOGA + 1) {
        if (l <= dp[x][i]) {
          chmin(ans[j], i);
        }
      }
    }
  }

  for (auto e : ans) {
    cout << (e == INF ? 0 : e) << ' ';
  }
  cout << '\n';
}
