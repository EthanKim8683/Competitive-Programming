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

const int LOGX = 20;
const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // a range is effectively a 4-pile nim game: l1-1, x1-r1, l2-1, x2-r2
  //
  // alice loses if their xor sum is 0
  //
  // probability of losing is the number of ranges with (l2-1)^(x2-r2)= the xor
  // of the range she chose
  //
  // maybe try all xors first and then we can construct later?
  //
  // set bits contribute fixed amt. unset bits might not: shift unset bits up 1,
  // then see how many subsets are le x2-1
  //
  // digit dp

  int T;
  cin >> T;

  while (T--) {
    int X1, X2;
    cin >> X1 >> X2;

    auto le = [&](int mask, int x) -> int {
      vc dp(LOGX + 1, vi(2, 0));
      dp[0][1] = 1;
      rep(i, 0, LOGX) {
        rep(j, 0, (mask >> (LOGX - 1 - i) & 1) + 1) {
          rep(k, 0, 2) {
            int d = x >> (LOGX - 1 - i) & 1;
            if (k == 1 and j > d) continue;
            dp[i + 1][k and j == d] += dp[i][k];
          }
        }
      }
      return dp[LOGX][0] + dp[LOGX][1];
    };

    auto f = [&](int x) -> int {
      return x < X2 ? le((x ^ ((1 << LOGX) - 1)) << 1, X2 - 1 - x)
                          << __builtin_popcount(x)
                    : 0;
    };

    pii best = {INF, -1};
    rep(i, 0, X1) { chmin(best, pii{f(i), i}); }
    cout << best.sd + 1 << ' ' << X1 << '\n';
  }
}
