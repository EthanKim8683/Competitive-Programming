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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  string S;
  cin >> S;

  int N = sz(S);

  auto check = [&](string s) -> char {
    int n = sz(s);

    vc dp(N + 1, vc<char>(N + 1, false));
    for (int i = N - 1; i >= 0; i--) {
      dp[i][i] = true;
      rep(j, i, N) {
        dp[i][j + 1] |= dp[i][j] and S[j] == s[(j - i) % n];
        for (int k = j + n; k <= N; k += n) {
          dp[i][k] |= dp[i][j] and dp[j][k];
        }
      }
    }
    return dp[0][N];
  };

  auto key = [&](string s) -> pair<int, string> { return {sz(s), s}; };

  string ans = S;
  rep(i, 1, N + 1) {
    if (N % i != 0) continue;
    rep(j, 0, N - i + 1) {
      string s = S.substr(j, i);
      if (key(s) < key(ans) and check(s)) {
        ans = s;
      }
    }
  }
  cout << ans << '\n';
}
