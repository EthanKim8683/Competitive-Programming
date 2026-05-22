#ifndef L
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

const int INF = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi B;
    int odds = 0;
    for (auto e : A) {
      if (e % 2 == 0) {
        B.pb(e);
      } else {
        B.pb(3 * e + 1);
        odds++;
      }
    }

    vi dp(odds + 1, -INF);
    dp[odds] = 0;
    rep(i, 0, N) {
      vi dp2 = dp;
      for (int x = B[i], even = 0; even <= odds;) {
        x = x / 2;

        vi dp3(odds + 1, -INF);
        if (x % 2 == 1) {
          rep(j, 1, odds + 1) {
            chmax(dp3[j], dp2[j] + 2);
            chmax(dp[j], dp2[j] + 2);
          }
          x = 3 * x + 1;
        } else {
          rep(j, 1, odds + 1) {
            chmax(dp3[j - 1], dp2[j] + 2);
            chmax(dp[j - 1], dp2[j] + 2);
          }
          even++;
        }
        dp2 = dp3;
      }
    }
    cout << dp[0] << '\n';
  }
}
