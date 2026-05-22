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

  // we basically do a bunch of averages until the differences are
  // infinitesimally small
  //
  // split into ranges and average them
  //
  // ranges must be strictly increasing
  //
  // within ranges must be size 2 or strictly non-decreasing

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    auto less = [&](pii a, pii b) -> bool { return a.fs * b.sd < b.fs * a.sd; };

    vc<pii> dp(N + 1, {1, 0});
    dp[0] = {0, 1};
    rep(i, 0, N) {
      rep(j, 1, N + 1 - i) {
        pii x = {accumulate(A.begin() + i, A.begin() + i + j, 0ll), j};
        if ((j <= 2 or is_sorted(A.begin() + i, A.begin() + i + j)) and
            (less(dp[i], x) and less(x, dp[i + j]))) {
          dp[i + j] = x;
        }
      }
    }
    for (auto [a, b] : dp) {
      cerr << a << '/' << b << ' ';
    }
    cerr << '\n';
    cout << (dp[N] == pii{1, 0} ? "No" : "Yes") << '\n';
  }
}
