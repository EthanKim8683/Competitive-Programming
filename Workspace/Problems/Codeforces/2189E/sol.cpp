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

const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // cost is effectively number of operations
  //
  // if there's a 1, there's always a solution
  //
  // we can make a subarray have difference 1
  //
  // at most 4 operations
  //
  // if 0 is not majority, at most 1 operation
  //
  // if there's a 11, try to get 2 operations
  // operate on one side, then operate on all
  //
  // if there's no 11, if we start or end with 1, at most 2 operations
  // this is the best we can do
  //
  // jk. do a small dp

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    string S;
    cin >> S;

    if (find(all(S), '1') == S.end()) {
      cout << "-1\n";
      continue;
    }

    if (S == "1") {
      cout << N - 1 << '\n';
      continue;
    }

    vi ps(N + 1);
    rep(i, 0, N) {
      if (S[i] == '0') {
        ps[i + 1] = 1;
      } else {
        ps[i + 1] = -1;
      }
    }
    rep(i, 0, N) { ps[i + 1] += ps[i]; }

    vi dp(3, INF), dp2(3, INF);
    vc<map<int, int>> dp3(3);
    dp[0] = ps[N] - ps[0];
    for (auto e : ps) {
      rep(i, 0, 3) {
        chmin(dp[i], dp2[i] - e + 1);
        if (!dp3[i].contains(e)) {
          dp3[i][e] = INF;
        }
        chmin(dp[i], dp3[i][e] - 1);
      }

      rep(i, 0, 3 - 1) {
        chmin(dp2[i + 1], dp[i] + e);
        if (!dp3[i + 1].contains(e)) {
          dp3[i + 1][e] = INF;
        }
        chmin(dp3[i + 1][e], dp[i]);
      }
    }
    int ans = N + 3;
    rep(i, 0, 3) {
      if (dp[i] <= 0) {
        chmin(ans, N + i);
      }
    }
    cout << ans << '\n';
  }
}
