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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int N, L, R;
    cin >> N >> L >> R;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi ps(N + 1);
    ps[0] = 0;
    rep(i, 0, N) { ps[i + 1] = ps[i] + A[i]; }

    vc<vi> insert(N + 2), erase(N + 2);
    multiset<int> S;
    vi dp(N + 1, 0);
    rep(i, 0, N + 1) {
      for (auto e : insert[i]) {
        S.insert(e);
      }
      for (auto e : erase[i]) {
        S.erase(S.find(e));
      }
      if (sz(S) > 0) {
        chmax(dp[i], *S.rbegin());
      }
      if (i < N) {
        chmax(dp[i + 1], dp[i]);
      }
      // ps[j] - ps[i] >= l
      // ps[j] >= ps[i] + l
      // ps[j] - ps[i] > r
      // ps[j] > ps[i] + r
      // cerr << lower_bound(all(ps), ps[i] + L) - ps.begin() << ' '
      //      << upper_bound(all(ps), ps[i] + R) - ps.begin() << '\n';
      insert[lower_bound(all(ps), ps[i] + L) - ps.begin()].pb(dp[i] + 1);
      erase[upper_bound(all(ps), ps[i] + R) - ps.begin()].pb(dp[i] + 1);
    }
    // cerr << '\n';
    cout << dp[N] << '\n';
  }
}
